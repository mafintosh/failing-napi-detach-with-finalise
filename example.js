var example = require('./build/Release/failing_detach_test.node')

const buf = example.alloc_with_finalise()
console.log(buf)

example.detach(buf)
console.log(buf)
