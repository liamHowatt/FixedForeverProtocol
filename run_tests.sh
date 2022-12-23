set -e

gcc -shared -fPIC -Wall lib/base64/ffp_base64.c -o lib/base64/ffp_base64.so
python3 tests/ffp_base64.py
rm lib/base64/ffp_base64.so

gcc -shared -fPIC -Wall lib/CircularBuffer/ffp_CircularBuffer.c -o lib/CircularBuffer/ffp_CircularBuffer.so
python3 tests/ffp_CircularBuffer.py
rm lib/CircularBuffer/ffp_CircularBuffer.so

gcc -shared -fPIC -Wall lib/crc32/ffp_crc32.c -o lib/crc32/ffp_crc32.so
python3 tests/ffp_crc32.py
rm lib/crc32/ffp_crc32.so

gcc -shared -fPIC -Wall lib/pseudorandom/ffp_pseudorandom.c -o lib/pseudorandom/ffp_pseudorandom.so
python3 tests/ffp_pseudorandom.py
rm lib/pseudorandom/ffp_pseudorandom.so
