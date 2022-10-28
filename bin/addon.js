const os = require('os');
module.exports = require(`./addon-${process.platform}-${process.arch}.node`);
