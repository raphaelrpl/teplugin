'use strict';

const fs = require('fs');
const chalk = require('chalk');

const CMAKETXT = 'CMakeLists.txt';
const CMAKECMD = 'cmake';

/**
 * Run CMake command with provided arguments
 *
 * @param {any} spawn - Spawn executor
 * @param {*} pDir - Base directory
 * @param {*} args
 */
exports.cmake = function (spawn, pDir, args) {
  var cmakeCmdArg = '';
  if (pDir && fs.existsSync(pDir)) {
    cmakeCmdArg = pDir + '/' + CMAKETXT;
  } else {
    cmakeCmdArg = CMAKETXT;
  }

  if (cmakeCmdArg === '') {
    this.log(chalk.red('Unable to regenerate makefile, project directory does not exist.'));
  } else {
    return spawn(CMAKECMD, [cmakeCmdArg, args]);
  }
};

