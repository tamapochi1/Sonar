module CIC
#(parameter
	bit_width = 17,
	decimation_ratio = 16
)
(
	input  wire clk,
	input  wire reset_n,
	input  wire signed [7:0] in,
	output reg out_valid,
	output reg signed [7:0] out
);


reg signed [bit_width-1:0] d_temp, d_d_temp;

reg signed [bit_width-1:0] d1;
reg signed [bit_width-1:0] d2;
reg signed [bit_width-1:0] d3;
reg signed [bit_width-1:0] d4;

reg signed [bit_width-1:0] d5, d_d5;
reg signed [bit_width-1:0] d6, d_d6;
reg signed [bit_width-1:0] d7, d_d7;
reg signed [bit_width-1:0] d8;

reg [7:0] count;

reg valid_comb;

always @(posedge clk)
 begin
 
	if(~reset_n)
	 begin
	 
		d1 <= 0;
		d2 <= 0;
		d3 <= 0;
		d4 <= 0;
		count <= 0;
		d_temp <= 0;
		
	 end
	else
	 begin
	 
		d1 <= in + d1;
		d2 <= d1 + d2;
		d3 <= d2 + d3;
		d4 <= d3 + d4;
		
		if(count == decimation_ratio - 1)
		 begin
		
			count <= 16'b0;
			d_temp <= d4;
			valid_comb <= 1'b1;
			
		 end
		else
		 begin
			
			count <= count + 16'd1;
			valid_comb <= 1'b0;
			
		 end
	 end
 end

always @(posedge clk)
 begin
	
	out_valid <= valid_comb;
	
	if(~reset_n)
	 begin
	 
		d_d_temp <= 0;
		d5 <= 0;
		d6 <= 0;
		d7 <= 0;
		d8 <= 0;
		d_d5 <= 0;
		d_d6 <= 0;
		d_d7 <= 0;
		out <= 0;
		
	 end
	else if(valid_comb)
	 begin
		
		d_d_temp <= d_temp;
		
		d5 <= d_temp - d_d_temp;
		d_d5 <= d5;
		
		d6 <= d5 - d_d5;
		d_d6 <= d6;
		
		d7 <= d6 - d_d6;
		d_d7 <= d7;
		
		d8 <= d7 - d_d7;
		
		out <= d8 >>>(bit_width - 8);
		
	 end
 end

 
endmodule
