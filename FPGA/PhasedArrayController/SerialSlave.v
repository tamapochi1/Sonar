module SerialSlave(
	input  wire res_n,
	input  wire SCK,
	input  wire RXD,
	output wire TXD,
	input  wire [7:0] sendData,
	output wire [7:0] recievedData,
	output wire recieved
);

wire nSCK = ~SCK;

reg [7:0] sendBuffer;
reg [7:0] recieveBuffer;
reg [3:0] BitCounter;

assign TXD = sendBuffer[0];
assign recievedData = recieveBuffer;
assign recieved = (BitCounter == 4'h8);
 
always @(posedge SCK or posedge nSCK or negedge res_n)
 begin
 
 	if (res_n == 1'b0)
	 begin
	 
		sendBuffer <= 8'h0;
		recieveBuffer <= 8'h0;
		BitCounter <= 4'h8;
		
	 end
	else if (SCK == 1'b1)
	 begin
	 
		recieveBuffer <= {RXD, recieveBuffer[7:1]};
		BitCounter <= BitCounter + 4'h1;
	 
	 end
	else
	 begin
	 
		if (BitCounter == 4'h8)
		 begin
		
			BitCounter <= 4'h0;
			sendBuffer <= sendData;
		
		 end
		else
		 begin
		
			sendBuffer <= {1'b0 ,sendBuffer[7:1]};
		
		 end
	 
	 end
	
 end

endmodule
