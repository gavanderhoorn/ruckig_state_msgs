#!/usr/bin/env python3

# Copyright (c) 2021, G.A. vd. Hoorn
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


# Converts enums from Ruckig's input_parameter.hpp to ROS msg files with
# constants (one file per enum).
#
# Probably brittle, but saves a bit of work when those enums get updated.


import argparse
import datetime
import os
import re
import sys

from CppHeaderParser import CppHeader


msg_preamble="""
# Auto-generated on {stamp} from:
#
#  {source_file}
#
# Any modifications will be lost upon regeneration.

# Enum-level Doxygen for {enum_name}:
#
#  "{enum_doxy}"
#

"""

msg_value_field="""# data
{enum_type} value
"""


def main():
    parser = argparse.ArgumentParser(formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument('--msg-dir', type=str, metavar='DIR', default='msg',
        help='Directory to write (updated) msg files to')
    parser.add_argument('HDR', help='Path to Ruckig input_parameter.hpp')
    args = parser.parse_args()

    msg_dir = os.path.abspath(args.msg_dir)
    if not os.path.isdir(msg_dir):
        sys.stderr.write(
            f"Can't seem to find the 'msg' dir at '{msg_dir}', aborting\n")
        sys.exit(1)

    parsed_h = CppHeader(args.HDR)
    if not parsed_h.enums:
        sys.stderr.write(
            f"No enums found in header (is this the correct header?), aborting\n")
        sys.exit(2)
    # we expect at least some enums we know in there
    flambda = lambda enum: enum['name'] in ['Result', 'DurationDiscretization']
    if not list(filter(flambda, parsed_h.enums)):
        sys.stderr.write(
            "Probably not a Ruckig header (could not find any known enums), "
            "aborting\n")
        sys.exit(3)

    parse_stamp = datetime.datetime.now().isoformat()
    source_file = os.path.abspath(args.HDR)

    for enum in parsed_h.enums:
        sys.stdout.write(f"Processing '{enum['name']}': ")

        ename = enum['name']
        efilename = f'{ename}.msg'
        edoxy = enum.get('doxygen', '').replace('//!', '').strip()
        etype = cpp_type_to_ros_msg_idl_type(enum['type'])

        # InternalState.msg already exists, and is not auto-generated
        if ename == 'InternalState':
            raise ValueError("Conflict with existing InternalState message, aborting")

        enum_vals = []
        for val in enum['values']:
            enum_vals.append({
                'name' : to_snake_case(val['name']).upper(),
                'doxy' : val.get('doxygen', '').replace('///<', '').strip(),
                'val'  : str(val['value']).replace(' ', '').strip(),
                'type' : etype,
            })

        outputf = f'{msg_dir}/{efilename}'
        print(f"writing {len(enum_vals)} constants to '{outputf}' ..")

        with open(outputf, 'w') as fout:
            tdict = {
                'source_file' : source_file,
                'stamp' : parse_stamp,
                'enum_name' : ename,
                'enum_doxy' : edoxy,
            }
            write_msg_file(tdict, enum_vals, fout)

    print(f"Generated {len(parsed_h.enums)} messages")


def to_snake_case(camel_str):
    # LikeThis -> like_this
    return re.sub(r'(?<!^)(?=[A-Z])', '_', camel_str).lower()


def cpp_type_to_ros_msg_idl_type(cpp_type):
    if cpp_type == int:
        return 'int32'
    raise ValueError(f"Unrecognised C++ enum base type: '{cpp_type}'")


def write_msg_file(template_dict, constants, out):
    out.write(msg_preamble.format(**template_dict))
    for c in constants:
        out.write(f"# {c['doxy']}\n{c['type']} {c['name']}={c['val']}\n\n")
    out.write(msg_value_field.format(enum_type=c['type']))


if __name__ == '__main__':
    main()
