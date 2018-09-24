'use strict';

const assert = require('yeoman-assert');
const helpers = require('yeoman-test');
const os = require('os');
const path = require('path');

describe('teplugin:app with no arguments, but options', () => {
  const appname = 'myplugin';
  const description = "The plugins displays a Helloworld content in TerraView";
  const destination = path.join(os.tmpdir(), 'test-teplugin');
  const terralibDir = '/opt/terralib/5.4.1';

  beforeEach(() => {
    return helpers.run(path.join(__dirname, '../generators/app'))
      .inDir(destination)
      .withOptions({doNotMake: true})
      .withPrompts({ appname, description, name: appname, projectDir: true, terralibDir });
  });

  const files = [
    `${appname}/CMakeLists.txt`,
    `${appname}/src/Plugin.h`,
    `${appname}/src/Plugin.cpp`,
    `${appname}/${appname}.teplg.json`
  ];

  it('creates files', () => {
    assert.file(files);
  });

  it('creates correct file content', () => {
    assert.fileContent(`${appname}/CMakeLists.txt`, `project("${appname}")`);
    assert.fileContent(`${appname}/CMakeLists.txt`, `add_library(${appname}`);
    assert.fileContent(`${appname}/src/Plugin.h`, `__TERRALIB_${appname.toUpperCase()}_PLUGIN_H`);
    assert.fileContent(`${appname}/${appname}.teplg.json`, `${description}`);

    const today = new Date().toLocaleDateString('en-US');

    assert.fileContent(`${appname}/${appname}.teplg.json`, `${today}`);
  });
});

describe('teplugin:app with arguments, without options', () => {
  const appname = 'myplugin';
  const description = "The plugins displays a Helloworld content in TerraView";
  const terralibDir = '/opt/terralib/5.4.1';
  const destination = path.join(os.tmpdir(), 'test-teplugin-arguments');

  beforeEach(() => {
    return helpers.run(path.join(__dirname, '../generators/app'))
      .inDir(destination)
      .withOptions({doNotMake: true})
      .withArguments([appname, description, terralibDir])
  });

  const files = [
    `${appname}/CMakeLists.txt`,
    `${appname}/src/Plugin.h`,
    `${appname}/src/Plugin.cpp`,
    `${appname}/${appname}.teplg.json`
  ];

  it('creates files', () => {
    assert.file(files);
  });

  it('creates correct file content', () => {
    assert.fileContent(`${appname}/CMakeLists.txt`, `project("${appname}")`);
    assert.fileContent(`${appname}/CMakeLists.txt`, `add_library(${appname}`);
    assert.fileContent(`${appname}/${appname}.teplg.json`, `${description}`);
    assert.fileContent(`${appname}/src/Plugin.h`, `__TERRALIB_${appname.toUpperCase()}_PLUGIN_H`);
  });
});


describe('teplugin:app with invalid TerraLib directory', () => {
  const appname = 'myplugin';
  const terralibDir = '/it/does/not/exists';
  const destination = path.join(os.tmpdir(), 'test-teplugin-invalid');

  beforeEach(() => {
    return helpers.run(path.join(__dirname, '../generators/app'))
      .inDir(destination)
      .withOptions({doNotMake: true})
      .withPrompts({ appname, terralibDir })
  });

  const files = [
    `${appname}/CMakeLists.txt`,
    `${appname}/src/Plugin.h`,
    `${appname}/src/Plugin.cpp`,
    `${appname}/${appname}.teplg.json`
  ];

  it('does not create files', () => {
    assert.noFile(files);
  });
});