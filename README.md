# node-fann2

node-fann is a [FANN](http://leenissen.dk/fann/) bindings for [Node.js](http://nodejs.org).

FANN (Fast Artificial Neural Network Library) is a free open source neural network library, which implements multilayer artificial neural networks with support for both fully connected and sparsely connected networks.

Forked from git://github.com/rlidwka/node-fann.git
Updated for Windows, Fann 2.2 and Node 4

## Installation on windows with VisualStudio Comunity 2015
1. You will need [FANN library](http://leenissen.dk/fann/wp/download/) version _>= 2.2.0_ (libfann2).

2. Compile in VS2015 and locate fanndouble.dll and fanndouble.lib

3. Make accesible for node the library "fanndouble.dll" (copy to %WINDIR%, [NODE_INSTALL_DIR] or %APPDATA%\npm)

4. Update node-gype 'npm install -g node-gyp'
   http://stackoverflow.com/questions/38149603/npm-install-fails-with-error-c2373-with-vs2015-update-3
   if doesn't work mind the nod-gyp directory (may use global npm dir instead of node install dir)

5. Copy devel files to node-gyp installation (Mind the name change):
   fanndouble.lib -> %USER_PROFILE%\.node-gyp\[version]\Release\doublefann.lib
   [FANN-Source]\src\include\*.h -> %USER_PROFILE%\.node-gyp\[version]\include
 
6. Run `npm install fann2` to install this package.

## Example

```javascript
var fann = require('fann2');
var net = new fann.net()

net.standard(2,3,1);

var data = [
    [[0, 0], [0]],
    [[0, 1], [1]],
    [[1, 0], [1]],
    [[1, 1], [0]],
];

net.train(data, {error: 0.00001});

console.log("xor test (0,0) -> ", net.run([0, 0]));
console.log("xor test (1,0) -> ", net.run([1, 0]));
console.log("xor test (0,1) -> ", net.run([0, 1]));
console.log("xor test (1,1) -> ", net.run([1, 1]));
```
