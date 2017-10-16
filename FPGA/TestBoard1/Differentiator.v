module Differentiator(
	input  wire clk,
	input  wire reset,
	input  wire [16:0] in,
	output wire [16:0] out
);

reg [16:0] preData;
reg [16:0] result;

assign out = result;

always @(posedge reset)
 begin
 
	preData <= 17'd0;
	
 end

always @(posedge clk)
 begin

	result <= in - preData;
	
 end

always @(negedge clk)
 begin
 
	preData <= in;
	
 end

endmodule
