module SerialSlave(
	input  wire clk,
	
	input  wire RSPCK,
	input  wire MOSI,
	output wire MISO,
	input  wire SSL,
	
	input  wire [7:0] sendData,
	output wire [7:0] recievedData,
	output wire recieved
);

reg [7:0] sendBuffer;
reg [2:0] sendingBitCounter;
reg [7:0] recieveBuffer;
reg [2:0] recievedBitCounter;


assign recieved = (recievedBitCounter == 2'h3);

always @(posedge clk)
 begin

 end

always @(negedge SSL)
 begin
	recievedBitCounter <= 3'h0;
	sendingBitCounter <= 3'h0;
 end


always @(posedge RSPCK)
 begin
	recieveBuffer <= {recieveBuffer[6:0], MOSI};
 end
 
always @(negedge RSPCK)
 begin
	recievedBitCounter <= recievedBitCounter + 3'h1;
	sendingBitCounter <= sendingBitCounter + 3'h1;
 end

endmodule
