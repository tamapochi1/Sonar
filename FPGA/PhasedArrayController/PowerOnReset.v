module PowerOnReset(
	input  wire clk,
	input  wire pll_locked,
	output wire res_n
);

reg por;
reg [12:0] por_counter;
always @(posedge clk)
 begin
 
	if (pll_locked == 1'b0)
	 begin
	 
		por_counter <= 13'd0;
		por <= 1'b0;
		
	 end
	else if (por_counter < 13'h00F)
	 begin
	 
		por <= 1'b1;
		por_counter <= por_counter + 13'h1;
		
	 end
	else if (por_counter < 13'hFFF)
	 begin
	 
		por <= 1'b0;
		por_counter <= por_counter + 13'h1;
		
	 end
	else
	 begin
	 
		por <= 1'b1;
		por_counter <= por_counter;
		
	 end
 end
 
assign res_n = por;

endmodule
