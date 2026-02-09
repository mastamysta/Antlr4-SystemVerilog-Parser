module foo
(
    input wire clk,
    input wire rstn,
    output logic out
);

logic unused;

always @(posedge clk) begin
    out <= unused;

    if (!rstn) begin
        out <= 1;
    end
end

always @(posedge out) begin
    
    unused <= ~out;

    if (!rstn) begin
        unused <= 1;
    end
end

endmodule