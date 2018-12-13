# make-source file_name [path] [--benchmark | -b]
# Creates a header and source file, test file, and optionally a benchmark file.
# header is created in current directory or in provided relative/absolute path.
# source is created in mirrored directory under src/ if public, or in same
# directory as header if private.
# Path must exist already.
# test created under tests/ in project directory.
# benchmark created under benchmarks/ in project directory.
# Creates a private header if called from under the src/ tree.
# Creates a public header if called from under the include/ tree.
