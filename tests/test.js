//const noppai = require('bindings')('noppai');

//const oppai = noppai(__dirname + "/testmap.osu");

//const pp = oppai.CalculatePP();

//console.dir(oppai.CalculatePP());
//console.dir(oppai.CalculateStars());

const noppai = require('../');

const calculator = noppai("tests/testmap.osu");

console.dir(calculator.CalculatePP());