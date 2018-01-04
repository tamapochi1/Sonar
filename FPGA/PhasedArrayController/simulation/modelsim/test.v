`timescale 1ns/1ns

`define CLK_CYCLE 41.6667	// ns
`define FINISH_COUNT 1000	// cycle

module test();

reg clk;
initial clk = 1'b0;
always #(`CLK_CYCLE / 2) clk = ~clk;

reg [15:0] timeCounter;
initial timeCounter = 16'h0;

always @(posedge clk)
 begin
	timeCounter <= timeCounter + 16'h1;
 end

always @*
 begin
	if(timeCounter == `FINISH_COUNT)
	 begin
		$stop;
	 end
 end

wire [36:0] speakers;

initial
 begin

 end

TOP target
(
	.clk24(clk),
	.speakers(speakers)
);

endmodule
