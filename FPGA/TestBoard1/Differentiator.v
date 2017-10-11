module Differentiator(
	input  wire clk,
	input  wire [16:0] in,
	output wire [16:0] out
);

reg [16:0] preData;
reg [16:0] result;

always @(posedge clk)
 begin

	result <= in - preData;
	
 end

always @(negedge clk)
 begin
 
	preData <= in;
	
 end

endmodule
