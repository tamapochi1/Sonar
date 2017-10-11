module Integrator(
	input  wire clk,
	input  wire [16:0] in,
	output wire [16:0] out
);

reg [16:0] result;

assign out = result;

always @(posedge clk)
 begin

	result <= in + result;
	
 end

endmodule
