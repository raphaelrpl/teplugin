'use strict';
const chalk = require('chalk');
const fs = require('fs');
const Generator = require('yeoman-generator');
const packageName = require('../../package.json').name;
const path = require('path');
const util = require('../util');
const yosay = require('yosay');

/**
 * Validates TerraLib directory.
 *
 * The validation consists in the following principles:
 *
 * - Checks for TerraLib CMake dir located inside lib/cmake/terralib-X.X.X;
 * - Check for TerraLib include/terralib.h or lib/libterralib*
 *
 * @throws {Error} Directory exceptions (permission/enoent) when directory is inconsistent
 * @param {string} directory - Contains input TerraLib directory
 * @returns {boolean} Returns if it is a valid directory
 */
function validateTerraLibDirectory(directory) {
  // Mount TerraLib CMake Directory to check
  const cmakeDirectory = path.join(directory, 'lib/cmake');

  // If found in cmake directory, assumes TerraLib installation
  if (fs.existsSync(cmakeDirectory) &&
      fs.readdirSync(cmakeDirectory).length > 0) {
    return true;
  }

  return false;
}

/**
 * Represents a Yeo Man Generator class to provide brief structure of TerraLib5 plugins.
 *
 * The generator just displays a dialog in TerraView application. It also adds a button in
 * menu bar "Plugins".
 *
 * Creates the following files:
 *
 * - Dialog.h   - Definition of Dialog in TerraView
 * - Dialog.cpp - Implementation of Dialog. Display only Alert box
 * - Plugin.h   - Definition of Plugin fundamentus, such start and shutdown operations. It also
 *                attaches Qt object signals from TerraView object manager.
 * - Plugin.cpp - Implementation of Plugin.h
 *
 * @example
 *
 * yo teplugin
 *
 * > Plugin name: helloworld
 * > Plugin description: This plugins display a helloworld message in TerraView
 * > Path to TerraLib: /opt/terralib/5.4.1
 *
 * @class Generator
 */
module.exports = class extends Generator {
  constructor(args, opts) {
    super(args, opts);
    this.argument('appname', {type: String, required: false});
    this.argument('description', {type: String, required: false});
    this.argument('terralibDir', {type: String, required: false});
    var notMakeOptArgs = {
      description: 'Skip the CMake generation of the makefile.',
      type: Boolean,
      default: false
    };

    // Option to run CMake command automatically. By default, false.
    this.option('doNotMake', notMakeOptArgs);
  }

  /**
   * Prompt user information
   */
  prompting() {
    // Have Yeoman greet the user.
    this.log(yosay(
      'Welcome to the awe-inspiring ' + chalk.red(packageName) + ' generator!'
    ));

    let prompts = [];

    // Only add this prompt if it was not specified as an argument.
    if (!this.options.appname) {
      prompts.push({
        type: 'input',
        name: 'name',
        message: 'Plugin name: ',
        default: this.config.get('appname') || this.appname
      });
    }

    if (!this.options.description) {
      prompts.push({
        type: 'input',
        name: 'description',
        message: 'Plugin Description: ',
        default: this.config.get('description') || this.appname
      });
    }

    if (!this.options.terralibDir) {
      prompts.push({
        type: 'input',
        name: 'terralibDir',
        message: 'Path to TerraLib: ',
        required: true
      });
    }

    return this.prompt(prompts)
      .then(answers => {
        if (answers.name) {
          this.options.appname = answers.name;
        }
        if (answers.terralibDir) {
          this.options.terralibDir = answers.terralibDir;
        }

        if (answers.description) {
          this.options.description = answers.description;
        }

        const terralibDir = this.options.terralibDir;
        try {
          // Checks TerraLib directory consistency
          validateTerraLibDirectory(terralibDir);

          this.options.projectDir = true;
          this.options.projectDirName = this.options.appname;

          // Store the supplied settings.
          this.config.set('appname', this.options.appname);
          this.config.set('terralibDir', this.options.terralibDir);
          this.config.set('projectDir', this.options.projectDir);
          this.config.set('projectDirName', this.options.projectDirName);
          this.config.save();
        } catch (error) {
          this.log(chalk.red(`An error occurred: ${error.message}`));
          process.exit(1);
        }
      });
  }

  writing() {
    var destination = '';
    if (this.options.projectDirName) {
      destination = this.options.projectDirName + '/';
    }

    const {appname, description, terralibDir} = this.options;

    const appnameUpper = appname.toUpperCase();

    this.fs.copyTpl(
      this.templatePath('CMakeLists.txt'),
      this.destinationPath(path.join(destination, 'CMakeLists.txt')),
      {appname: this.options.appname, terralibDir}
    );

    this.fs.copyTpl(
      this.templatePath('Plugin.h'),
      this.destinationPath(path.join(destination, 'src/Plugin.h')),
      {appnameUpper}
    );

    this.fs.copyTpl(
      this.templatePath('Plugin.cpp'),
      this.destinationPath(path.join(destination, 'src/Plugin.cpp')),
      {appnameUpper}
    );

    this.fs.copyTpl(
      this.templatePath('PluginDialog.h'),
      this.destinationPath(path.join(destination, 'src/PluginDialog.h')),
      {appnameUpper}
    );

    this.fs.copyTpl(
      this.templatePath('PluginDialog.cpp'),
      this.destinationPath(path.join(destination, 'src/PluginDialog.cpp')),
      {appnameUpper}
    );

    this.fs.copy(
      this.templatePath('PluginDialog.ui'),
      this.destinationPath(path.join(destination, 'src/ui/PluginDialog.ui')),
      { }
    );

    this.fs.copy(
      this.templatePath('_gitignore'),
      this.destinationPath(path.join(destination, '.gitignore'))
    );

    this.fs.copyTpl(
      this.templatePath('plugin.teplg.json'),
      this.destinationPath(path.join(destination, `${appname}.teplg.json`)),
      {appname, description, releaseDate: new Date().toLocaleDateString('en-US')}
    );
  }

  end() {
    var theName = this.options.appname;
    var createdMsg = 'Project ' + theName + ' has been created.';

    const {terralibDir} = this.options;

    if (this.options.doNotMake) {
      this.log(chalk.red(createdMsg));
      this.log(chalk.red('The automatic generation of the makefile has been skipped, run "CMake CMakeLists.txt" to generate the makefile for this project.'));
    } else {
      var cmake = util.cmake(this.spawnCommand, this.config.get('projectDirName'), `-DCMAKE_PREFIX_PATH=${terralibDir};${terralibDir}/3rdparty`);
      cmake.on('exit', function () {
        console.log(chalk.red(createdMsg));
      });
    }
  }
};
