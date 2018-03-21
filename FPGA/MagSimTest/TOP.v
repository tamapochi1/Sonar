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

genvar i;

/***  system   ***/

wire res_n;
wire pll_locked;
PowerOnReset por(.clk(clk24), .res_n(res_n), .pll_locked(pll_locked));

wire clk0_64;
wire clk4_8;
wire clk0_3;			// inner clock from PLL (640kHz; 40k * 16bits)
PLL pll(.inclk0(clk24), .c0(clk0_64), .c1(clk4_8), .c2(clk0_3), .locked(pll_locked));

assign LED[0] = 1'b0;
assign LED[1] = 1'b1;
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

wire [63:0] mult_result;

MULT mult_inst (
		.clk    (clk24),
		.areset (res_n),
		.en     (1'b1),
		.a      (64'h4019_21FB_5444_2D18),
		.b      ({register[15],register[14],register[13],register[12],register[11],register[10],register[9],register[8],
					 register[7],register[6],register[5],register[4],register[3],register[2],register[1],register[0]}),      //      b.b
		.q      (mult_result)       //      q.q
	);

wire [63:0] final_result;

DIV div_inst (
		.clk    (clk24),    //    clk.clk
		.areset (res_n), // areset.reset
		.en     (1'b1),     //     en.en
		.a      ({register[31],register[30],register[29],register[28],register[27],register[26],register[25],register[24],
					 register[23],register[22],register[21],register[20],register[19],register[18],register[17],register[16]}),      //      a.a
		.b      (mult_result),      //      b.b
		.q      (final_result)       //      q.q
	);


/***   MCU(PDC) I/F   ***/
wire output_ON;

assign output_ON = register[6'h32][0];
assign MICCLK[0] = clk4_8;
assign MICCLK[1] = clk4_8;

//generate
//	for (i = 1; i <= 12; i = i + 1)
//	 begin : GeneratedMics
//		Mic mic (.res_n(res_n), .clk4_8(clk4_8), .clk0_3(clk0_3), .dataIn(MIC[i]), .dataOut(results[i]));
//	 end
//endgenerate
//
//wire [20:0] results [1:12];
//wire [255:0] resultsBus = {
//	results[12], results[11], results[10], results[9], results[8], results[7],
//	results[6], results[5], results[4], results[3], results[2], results[1]};
	
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
	.data ( {192'd0, final_result} ),
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
