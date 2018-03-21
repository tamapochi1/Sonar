module PDC
#(
	parameter H_bytes = 4
)
(
	input  wire res_n,
	input  wire clk,
	
	input  wire output_ON,
	input  wire [7:0] data,
	output wire dataReadReq,
	output wire [11:0] index,
	
	output wire VSYNC,
	output wire HSYNC,
	output wire PIXCLK,
	output wire [7:0] PIXD
);

reg output_enable;
reg [11:0] H_Counter;
reg [15:0] clkCounter;
reg vsync;
reg hsync;
reg dataReadReqState;

assign dataReadReq = dataReadReqState;
assign index = H_Counter;
assign VSYNC = vsync;
assign HSYNC = hsync;
assign PIXCLK = clk;
assign PIXD = data;

always @(negedge clk or negedge res_n)
 begin
 
	if (res_n == 1'b0)
	 begin
	 
		H_Counter <= 12'h000;
		clkCounter <= 16'h0000;
		vsync <= 1'b0;
		hsync <= 1'b0;
		dataReadReqState <= 1'b0;
		output_enable <= 1'b0;
		
	 end
	else if (~output_enable && output_ON)
	 begin
	 
		output_enable <= 1'b1;
		H_Counter <= 12'h000;
		clkCounter <= 16'h0000;
		vsync <= 1'b0;
		hsync <= 1'b0;
		dataReadReqState <= dataReadReqState;
	 
	 end
	else if (output_enable)
	 begin
	 
		clkCounter <= clkCounter + 16'd1;
	 
		if (clkCounter < 16'd128)
		 begin
			
			output_enable <= output_enable;
			vsync <= 1'b0;
			hsync <= 1'b0;
			dataReadReqState <= dataReadReqState;
			
		 end
		else if (clkCounter < 16'd137)
		 begin
		 
			output_enable <= output_enable;
			vsync <= 1'b1;
			hsync <= 1'b0;
			dataReadReqState <= dataReadReqState;
		 
		 end
		else if (clkCounter == 16'd137)
		 begin
		 
			output_enable <= output_enable;
			vsync <= 1'b1;
			hsync <= 1'b0;
			dataReadReqState <= 1'b1;
		 
		 end
		else if (clkCounter == 16'd138)
		 begin
		 
			output_enable <= output_enable;
			vsync <= 1'b1;
			hsync <= 1'b1;
			H_Counter <= 12'h000;
			dataReadReqState <= dataReadReqState;
		 
		 end
		else if (clkCounter < 16'd137 + H_bytes)
		 begin
		 
			output_enable <= output_enable;
			vsync <= 1'b1;
			hsync <= 1'b1;
			H_Counter <= H_Counter + 12'h001;
			dataReadReqState <= dataReadReqState;
		 
		 end
		else if (clkCounter == 16'd137 + H_bytes)
		 begin
		 
			output_enable <= output_enable;
			vsync <= 1'b1;
			hsync <= 1'b1;
			H_Counter <= H_Counter + 12'h001;
			dataReadReqState <= 1'b0;
		 
		 end
		else if (clkCounter == 16'd138 + H_bytes)
		 begin
		 
			output_enable <= output_enable;
			vsync <= 1'b1;
			hsync <= 1'b0;
			dataReadReqState <= dataReadReqState;
		 
		 end
		else if (clkCounter < 16'd148 + H_bytes)
		 begin
		 
			output_enable <= output_enable;
			vsync <= 1'b1;
			hsync <= 1'b0;
			dataReadReqState <= dataReadReqState;
		 
		 end
		else
		 begin
		 
			output_enable <= 1'b0;
			clkCounter <= 16'h0000;
			vsync <= 1'b0;
			hsync <= 1'b0;
			dataReadReqState <= dataReadReqState;
		 
		 end
	 
	 end
 
 end

endmodule
