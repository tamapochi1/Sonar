module TOP(
	input  wire clk10,
	output wire [36:0] speakers
);

/*************************************

clk10		:[in] 10MHz clock input
speakers	:[out] output to driver ICs

----- register table -----
address | bits | function
--------+------+----------
 0x00            N/A
 0x01       1    0: output OFF / 1: output ON
 0x02       4    duty of output (ex. 0x8 : duty = 50%, 0x0 : duty = 0%)
 
 0x10       4    number of phase shifts for speaker0
 .          .                               .
 .          .                               .
 .          .                               .
 0x34       4    number of phase shifts for speaker36

*************************************/

parameter NUM_SPEAKERS = 37;

reg [7:0] addressBuf;		// received address from MCU
reg [3:0] register [0:63];	// control registers
reg [3:0] counter;			// used to generate baseSignal

wire clk;			// inner clock from PLL (640kHz; 40k * 16bits)
wire dataRecieved;
wire [7:0] data;
wire baseSignal;	// signal for speakers
wire speakersOn;	// 0: baseSignal counter OFF / 1: baseSignal counter ON

assign speakersOn = register[6'h01][0];
assign baseSignal = (counter < register[6'h02]) & speakersOn;

`ifdef SIMULATION
	assign clk = clk10;
`else
	PLL pll(.inclk0(clk10), .c0(clk));
`endif

genvar i;
generate
	for (i = 0; i < NUM_SPEAKERS; i = i + 1)
	 begin : GeneratedPhaseShifters
		PhaseShifter ps (.clk(clk), .shift(register[6'h10 + i]), .in(baseSignal), .out(speakers[i]));
	 end
endgenerate


always @(posedge dataRecieved)
 begin

	if (address)
	 begin
		addressBuf <= data;
	 end
	else
	 begin
		register[addressBuf] <= data[3:0];
	 end

 end

always @(posedge clk)
 begin

	if (speakersOn)
	 begin
		counter <= counter + 4'h1;
	 end
	else
	 begin
		counter <= 4'h0;
	 end

 end


endmodule
