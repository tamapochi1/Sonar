module TOP(
	input  wire clk48,
	output wire speaker,
	output wire pdwClk,
	input  wire pdwData,
	output wire pwmOut,
	output wire subClk,
	output wire [20:0] dataOut
);

wire clk4_8;
wire clk0_64;
wire clk0_3;
wire reset;
wire speaker_on;

assign pdwClk = clk4_8;
assign subClk = clk0_3;

PLL pll(.inclk0(clk48), .c0(clk4_8), .c1(clk0_64), .c2(clk0_3), .locked());

// Power ON Reset
reg por;
reg [15:0] por_counter;
always @(posedge clk48)
 begin
 
	if(por_counter != 16'h00FF)
	 begin
	 
		por <= 1'b0;
		por_counter <= por_counter + 16'h1;
		
	 end
	else
	 begin
	 
		por <= 1'b1;
		por_counter <= por_counter;
		
	 end
 end
assign reset = por;

reg [15:0] counter_slow;
always @(posedge clk0_64)
 begin
 
	if(counter_slow == 16'hFFFF || ~reset)
	 begin
		counter_slow <= 16'h0;
	 end
	else
	 begin
		counter_slow <= counter_slow + 16'h1;
	 end
	 
 end
assign speaker_on = (counter_slow < 16'h6F);

// Output 40kHz to Speaker.
reg [3:0] counter;
always @(posedge clk0_64)
 begin
 
	if(counter == 4'hF || ~reset)
	 begin
		counter <= 4'h0;
	 end
	else
	 begin
		counter <= counter + 4'h1;
	 end
	 
 end
assign speaker = (counter < 4'h8) & speaker_on;

// Receive PDW data from MIC.
reg signed [7:0] pdw_inputBuf;
always @(posedge pdwClk)
 begin
 
	if(~reset)
	 begin
		pdw_inputBuf <= 8'd0;
	 end
	else
	 begin
		pdw_inputBuf <= pdwData ? 8'b1 : -8'b1;
	 end

 end

wire signed [7:0] cic_result;
wire signed [20:0] fir_result;
wire cic_valid;
wire fir_valid;

CIC cic(
	.clk(pdwClk),
	.reset_n(reset),
	.in(pdw_inputBuf),
	.out(cic_result),
	.out_valid(cic_valid));


FIR fir(
	.ast_sink_data(cic_result),
	.ast_sink_valid(cic_valid),
	.ast_sink_error(2'b00),
	.ast_source_data(fir_result),
	.ast_source_valid(fir_valid),
	.clk(clk4_8),
	.reset_n(reset));

	
reg [20:0] fir_result_buf;
always @(posedge fir_valid)
 begin

	fir_result_buf <= fir_result;
	 
 end
	
wire [7:0] result;

//DIV div(.denom(16'h00FF), .numer(fir_result), .quotient(result));	// 死ぬほどLE使う。500以上？
assign result = fir_result_buf[17:10] + 7'd127;
assign dataOut = fir_result_buf;

PWM pwm(.clk(clk48), .reset_n(reset), .duty(result), .out(pwmOut));

endmodule
