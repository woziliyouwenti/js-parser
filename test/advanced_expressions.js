// Advanced expression coverage

var precedence = 1 + 2 * 3 - 4 / 2;
var grouped = (1 + 2) * (3 + 4);
var compare = x + 1 >= y - 2;
var logical = true || false && !false;
var bitwise = (a & b) | (c ^ d);
var shifts = value << 2 >> 1;
var assign = 1;
assign += 2;
assign <<= 1;

var choice = score > 60 ? "pass" : "fail";
var nestedChoice = score > 90 ? "A" : score > 80 ? "B" : "C";

