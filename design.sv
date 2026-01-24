module foo
(
    input wire clk,
    input wire rstn,
    output logic out
);

logic unused;

always @(posedge clk) begin
    out <= ~out;

    if (!rstn) begin
        out <= 1;
    end
end

endmodule