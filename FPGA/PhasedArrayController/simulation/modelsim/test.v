`timescale 1ns/1ns

`define CLK_CYCLE 100		// ns
`define FINISH_COUNT 300	// cycle

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

reg sync;
reg address;
reg [5:0] data;
wire [36:0] speakers;

initial
 begin
	sync = 1'b0;
	address = 1'b0;
	data = 6'h00;
 end

TOP target
(
	.clk10(clk),
	.sync(sync),
	.address(address),
	.data(data),
	.speakers(speakers)
);

always @*
 begin
	case(timeCounter)

// set duty to 50 %
	16'd10 :
	 begin
		sync <= 1'b0;
		address <= 1'b1;
		data <= 6'h02;
	 end
	16'd11 : sync <= 1'b1;

	16'd12 :
	 begin
		sync <= 1'b0;
		address <= 1'b0;
		data <= 6'h08;
	 end
	16'd13 : sync <= 1'b1;


// speaker0 : delay = 0
	16'd14 :
	 begin
		sync <= 1'b0;
		address <= 1'b1;
		data <= 6'h10;
	 end
	16'd15 : sync <= 1'b1;

	16'd16 :
	 begin
		sync <= 1'b0;
		address <= 1'b0;
		data <= 6'h00;
	 end
	16'd17 : sync <= 1'b1;

// speaker1 : delay = 1
	16'd18 :
	 begin
		sync <= 1'b0;
		address <= 1'b1;
		data <= 6'h11;
	 end
	16'd19 : sync <= 1'b1;

	16'd20 :
	 begin
		sync <= 1'b0;
		address <= 1'b0;
		data <= 6'h01;
	 end
	16'd21 : sync <= 1'b1;

// speaker2 : delay = 15
	16'd22 :
	 begin
		sync <= 1'b0;
		address <= 1'b1;
		data <= 6'h12;
	 end
	16'd23 : sync <= 1'b1;

	16'd24 :
	 begin
		sync <= 1'b0;
		address <= 1'b0;
		data <= 6'h0F;
	 end
	16'd25 : sync <= 1'b1;


// start
	16'd101 :
	 begin
		sync <= 1'b0;
		address <= 1'b1;
		data <= 6'h01;
	 end
	16'd102 : sync <= 1'b1;

	16'd103 :
	 begin
		sync <= 1'b0;
		address <= 1'b0;
		data <= 6'h01;
	 end
	16'd104 : sync <= 1'b1;

// stop
	16'd130 :
	 begin
		sync <= 1'b0;
		address <= 1'b1;
		data <= 6'h01;
	 end
	16'd131 : sync <= 1'b1;

	16'd132 :
	 begin
		sync <= 1'b0;
		address <= 1'b0;
		data <= 6'h00;
	 end
	16'd133 : sync <= 1'b1;

// start
	16'd201 :
	 begin
		sync <= 1'b0;
		address <= 1'b1;
		data <= 6'h01;
	 end
	16'd202 : sync <= 1'b1;

	16'd203 :
	 begin
		sync <= 1'b0;
		address <= 1'b0;
		data <= 6'h01;
	 end
	16'd204 : sync <= 1'b1;

// stop
	16'd230 :
	 begin
		sync <= 1'b0;
		address <= 1'b1;
		data <= 6'h01;
	 end
	16'd231 : sync <= 1'b1;

	16'd252 :
	 begin
		sync <= 1'b0;
		address <= 1'b0;
		data <= 6'h00;
	 end
	16'd253 : sync <= 1'b1;

	endcase
 end

endmodule
