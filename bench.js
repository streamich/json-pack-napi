const {readUtf8} = require('./main');

const iterations = 100e6;

const buf = new Uint8Array([65, 66, 67]);

var sum = 0;
const iteration = () => readUtf8(buf, 0, 1);

const t1 = performance.now();
for (let i = 0; i < iterations; i++) iteration();
const t2 = performance.now();

console.log('Result:', sum, 'Ops/sec:', (iterations / ((t2 - t1) / 1000) / 1e6).toFixed(1), 'M');
