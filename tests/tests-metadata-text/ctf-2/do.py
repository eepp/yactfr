import sys


cur_prefix = sys.argv[1]
new_prefix = sys.argv[2]
cur_fc_type = sys.argv[3]
new_fc_type = sys.argv[4]

for filename in sys.argv[5:]:
    with open(filename, 'r') as f:
        contents = f.read()

    new_filename = new_prefix + filename.replace(cur_prefix, '')
    contents = contents.replace(cur_fc_type, new_fc_type)

    with open(new_filename, 'w') as f:
        f.write(contents)
