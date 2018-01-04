module Mic(
	input  wire res_n,
	input  wire clk4_8,
	input  wire clk0_3,
	
	input  wire dataIn,
	output wire [20:0] dataOut
);

reg signed [7:0] inputBuf;
always @(posedge clk4_8)
 begin
 
	if(~res_n)
	 begin
		inputBuf <= 8'd0;
	 end
	else
	 begin
		inputBuf <= dataIn ? 8'b1 : -8'b1;
	 end

 end

wire signed [7:0] cic_result;
wire signed [20:0] fir_result;
wire cic_valid;
wire fir_valid;

CIC cic(
	.clk(clk4_8),
	.reset_n(res_n),
	.in(inputBuf),
	.out(cic_result),
	.out_valid(cic_valid));


FIR fir(
	.ast_sink_data(cic_result),
	.ast_sink_valid(cic_valid),
	.ast_sink_error(2'b00),
	.ast_source_data(fir_result),
	.ast_source_valid(fir_valid),
	.clk(clk4_8),
	.reset_n(res_n));

	
reg [20:0] fir_result_buf;
always @(posedge fir_valid)
 begin

	fir_result_buf <= fir_result;
	 
 end

assign dataOut = fir_result_buf;

endmodule
