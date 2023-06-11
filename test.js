const {readUtf8} = require('./main');
const {equal} = require('assert');

const buf1 = new Uint8Array([65, 66, 67]);
const buf2 = buf1.subarray(1);
const buf3 = new Uint8Array([0xf0, 0x9f, 0xa5, 0xb6]);

equal(readUtf8(buf1, 0, 1), 'A');
equal(readUtf8(buf1, 0, 2), 'AB');
equal(readUtf8(buf1, 1, 2), 'BC');
equal(readUtf8(buf2, 0, 1), 'B');
equal(readUtf8(buf2, 1, 1), 'C');
equal(readUtf8(buf2, 0, 2), 'BC');
equal(readUtf8(buf3, 0, 4), '🥶');
