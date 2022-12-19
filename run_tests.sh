set -e

gcc -shared -fPIC -Wall lib/base64/ffe_base64.c -o lib/base64/ffe_base64.so
python3 tests/ffe_base64.py
rm lib/base64/ffe_base64.so

gcc -shared -fPIC -Wall lib/CircularBuffer/ffe_CircularBuffer.c -o lib/CircularBuffer/ffe_CircularBuffer.so
python3 tests/ffe_CircularBuffer.py
rm lib/CircularBuffer/ffe_CircularBuffer.so

gcc -shared -fPIC -Wall lib/crc32/ffe_crc32.c -o lib/crc32/ffe_crc32.so
python3 tests/ffe_crc32.py
rm lib/crc32/ffe_crc32.so

gcc -shared -fPIC -Wall lib/pseudorandom/ffe_pseudorandom.c -o lib/pseudorandom/ffe_pseudorandom.so
python3 tests/ffe_pseudorandom.py
rm lib/pseudorandom/ffe_pseudorandom.so
