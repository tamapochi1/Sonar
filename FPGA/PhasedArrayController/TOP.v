module TOP(
	input  wire clk24,
	output wire [37:1] speakers,
	input  wire SCK,
	input  wire RXD,
	output wire TXD,
	input  wire PCKO,
	output wire VSYNC,
	output wire HSYNC,
	output wire PIXCLK,
	output wire [7:0] PIXD,
	input  wire [12:1] MIC,
	output wire [1:0] MICCLK,
	output wire [2:0] LED
);

/*************************************

clk24		:[in]  24MHz clock input
speakers	:[out] output to driver ICs

----- register table -----
address | bits | function
--------+------+----------

 0x01       1    0: output OFF / 1: output ON
 0x02       4    duty of output (ex. 0x8 : duty = 50%, 0x0 : duty = 0%)
 0x03       1    0: mic data output OFF / 1: mic data output ON
 0x04       3    LED control
 
 0x10       4    number of phase shifts for speaker0
 .          .                               .
 .          .                               .
 .          .                               .
 0x34       4    number of phase shifts for speaker36

*************************************/

genvar i;

/***  system   ***/

wire res_n;
wire pll_locked;
PowerOnReset por(.clk(clk24), .res_n(res_n), .pll_locked(pll_locked));

wire clk0_64;
wire clk4_8;
wire clk0_3;			// inner clock from PLL (640kHz; 40k * 16bits)
PLL pll(.inclk0(clk24), .c0(clk0_64), .c1(clk4_8), .c2(clk0_3), .locked(pll_locked));

assign LED[0] = speakersOn | output_ON;
assign LED[1] = register[6'h04][1];
assign LED[2] = 1'b1;

/***  MCU(Control) I/F   ***/

reg [3:0] register [0:63];	// control registers
reg [6:0] addressBuf;		// received address from MCU
wire dataRecieved;
wire [7:0] recievedData;

SerialSlave ss(
	.res_n(res_n), .clk(clk24),
	.SCK(SCK), .RXD(RXD), .TXD(TXD),
	.sendData(8'h00), .recievedData(recievedData), .recieved(dataRecieved));
	
always @(negedge dataRecieved)
 begin

	if (recievedData[7] == 1'b1)
	 begin
		addressBuf <= recievedData[6:0];
	 end
	else
	 begin
		register[addressBuf] <= recievedData[3:0];
	 end

 end


/***   speaker driver   ***/

reg [3:0] counter;
reg [3:0] pulseCounter;
wire baseSignal;
wire speakersOn_recieved;
reg speakersOn;
reg speakersOn_clr;

assign speakersOn_recieved = dataRecieved
									& (addressBuf == 7'h01)
									& (recievedData[7] == 1'b0)
									& recievedData[0];
									
assign baseSignal = (counter < register[6'h02]) & speakersOn;

generate
	for (i = 1; i <= 37; i = i + 1)
	 begin : GeneratedPhaseShifters
		PhaseShifter ps (.clk(clk0_64), .shift(register[6'h10 + i]), .in(baseSignal), .out(speakers[i]));
	 end
endgenerate

always @(posedge speakersOn_recieved or negedge speakersOn_clr)
 begin
 
	if(~speakersOn_clr)
	 begin
	 
		speakersOn <= 1'b0;
	 
	 end
	else
	 begin
	 
	 	speakersOn <= 1'b1;
	 
	 end
 
 end

always @(posedge clk0_64 or negedge res_n)
 begin

	if(~res_n)
	 begin
	 
		counter <= 4'd0;
		pulseCounter <= 4'd1;
		speakersOn_clr <= 1'b1;
	 
	 end
	else if (speakersOn)
	 begin
	 
		counter <= counter + 4'h1;
		
		if(counter == 4'hF)
		 begin
		 
			counter <= 4'h0;

			if(pulseCounter < 4'h4)
			 begin
	 
				speakersOn_clr <= 1'b1;
				pulseCounter <= pulseCounter + 4'h1;
	 
			 end
			else
			 begin
			 
				speakersOn_clr <= 1'b0;
				pulseCounter <= 4'd0;
			 
			 end
		 
		 end
		 
	 end
	else
	 begin
	 
		counter <= 4'h0;
		speakersOn_clr <= 1'b1;
		 
	 end

 end



/***   MCU(PDC) I/F   ***/
wire output_ON;

assign output_ON = register[6'h03][0];
assign MICCLK[0] = clk4_8;
assign MICCLK[1] = clk4_8;

generate
	for (i = 1; i <= 12; i = i + 1)
	 begin : GeneratedMics
		Mic mic (.res_n(res_n), .clk4_8(clk4_8), .clk0_3(clk0_3), .dataIn(MIC[i]), .dataOut(results[i]));
	 end
endgenerate

wire [20:0] results [1:12];
wire [255:0] resultsBus = {
	results[12], results[11], results[10], results[9], results[8], results[7],
	results[6], results[5], results[4], results[3], results[2], results[1]};
	
wire sampleClock;
reg sampleClockState;
assign sampleClock = sampleClockState;

always @(posedge clk0_3)
 begin
 
	if (~res_n)
	 begin
	 
		sampleClockState <= 1'b0;
	 
	 end
	else
	 begin
	 
		sampleClockState <= ~sampleClockState;
	
	 end
 
 end

FIFO	fifo (
	.data ( resultsBus ),
	.rdclk ( PCKO ),
	.rdreq ( rdreq ),
	.wrclk ( sampleClock ),
	.wrreq ( output_ON ),
	.q ( pdcData ),
	.rdusedw ( fifoCount )
	);
	
wire rdreq;
wire [7:0] pdcData;
wire [8:0] fifoCount;

PDC #(
	.H_bytes(256)
) pdc (
	.res_n(res_n), .clk(PCKO),
	.output_ON(fifoCount[8]), .data(pdcData), .dataReadReq(rdreq), .index(),
	.VSYNC(VSYNC), .HSYNC(HSYNC), .PIXCLK(PIXCLK), .PIXD(PIXD)
	);







endmodule
