`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:43:29 11/29/2017 
// Design Name: 
// Module Name:    fifo 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module fifo #(parameter B=8,W=4)(clk,reset,rd,wr,w_data,empty,full,r_data,pos,r_data_std);		//����λ����ַλ��
input clk,reset;
input rd,wr;
input [B-1:0]w_data;
output empty,full;
output [B-1:0]r_data;
output [W-1:0]pos;
output [B-1:0]r_data_std;



reg [B-1:0]array_reg [2**W-1:0];	//�Ĵ�������
reg [W-1:0]w_ptr_reg,w_ptr_next,w_ptr_succ;
reg [W-1:0]r_ptr_reg,r_ptr_next,r_ptr_succ;
reg full_reg,empty_reg,full_next,empty_next;
wire wr_en;

assign pos=r_ptr_reg;
//���岿��
//�Ĵ����ļ�д����
always@(posedge clk)
	if(wr_en)
		array_reg[w_ptr_reg]<=w_data;
		
//�Ĵ����ļ�������
assign r_data=array_reg[r_ptr_reg-1];
assign r_data_std=array_reg[r_ptr_reg];
//������ʱ��дʹ����Ч
assign wr_en=wr&~full_reg;	//wr�ǽӿڣ���ʾ��Ҫд

//FIFO�����߼�
//�Ĵ�����дָ��
always@(posedge clk,posedge reset)
	if(reset)
		begin
			w_ptr_reg<=0;
			r_ptr_reg<=0;
			//w_ptr_next<=0;
			//w_ptr_succ<=0;
			//r_ptr_next<=0;
			//r_ptr_succ<=0;
			full_reg<=1'b0;
			empty_reg<=1'b1;
		end
	else
		begin
			w_ptr_reg<=w_ptr_next;
			r_ptr_reg<=r_ptr_next;
			full_reg<=full_next;
			empty_reg<=empty_next;
		end
	
//��дָ�����һ״̬�߼�
//integer i;
always@(*)
begin
	//ָ���1����
	w_ptr_succ=w_ptr_reg+1;
	r_ptr_succ=r_ptr_reg+1;
	//Ĭ�ϱ���ԭֵ
	w_ptr_next=w_ptr_reg;
	r_ptr_next=r_ptr_reg;
	full_next=full_reg;
	empty_next=empty_reg;
	
	case({wr,rd})
		2'b01:	//������
			if(~empty_reg)	//�ǿ�
				begin
					r_ptr_next=r_ptr_succ;
					full_next=1'b0;
					if(r_ptr_succ==w_ptr_reg)
						empty_next=1'b1;
				end
		2'b10:	//д����
			if(~full_reg)	//����
				begin
					w_ptr_next=w_ptr_succ;
					empty_next=1'b0;
					if(w_ptr_succ==r_ptr_reg)
						full_next=1'b1;
				end
		2'b11:	//����д
			begin
				w_ptr_next=w_ptr_succ;
				r_ptr_next=r_ptr_succ;
			end
		//default:i=1;
	endcase
end

//���
assign full=full_reg;
assign empty=empty_reg;
endmodule

