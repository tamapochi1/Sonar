module PhaseShifter(
	input  wire clk,
	input  wire [3:0] shift,
	input  wire in,
	output wire out
);

reg [15:0] Q;

assign out = Q[shift];

always @(posedge clk)
begin

	Q <= {Q[14:0], in};

end

endmodule
