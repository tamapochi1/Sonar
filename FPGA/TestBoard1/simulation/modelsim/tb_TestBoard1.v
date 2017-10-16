`timescale 1ns/10ps

`define CLK_CYCLE 20.83		// ns
`define FINISH_COUNT 10000	// cycle

module tb_TestBoard1();

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


wire speaker;
wire pdwClk;
reg pdwData;
wire pwmOut;

initial
 begin
	pdwData = 1'b0;
 end

TOP target
(
	.clk48(clk),
	.speaker(speaker),
	.pdwClk(pdwClk),
	.pdwData(pdwData),
	.pwmOut(pwmOut)
);

initial
 begin
	target.por_counter = 0;
 end

always @(negedge pdwClk)
 begin
	#0		pdwData = 0;
	#100	pdwData = 1;
	#400	pdwData = 0;
	#500	pdwData = 1;
	#550	pdwData = 0;
	#1000	pdwData = 1;
	#1200	pdwData = 0;
	#100	pdwData = 1;
	#600	pdwData = 0;
	#100	pdwData = 1;
	#300	pdwData = 0;
	#200	pdwData = 1;
	#100	pdwData = 0;
 end


endmodule
