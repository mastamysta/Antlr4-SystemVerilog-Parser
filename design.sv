module foo
(
    input wire clk,
    input wire rstn,
    output logic out
);


always @(posedge clk) begin
    out <= ~out;

    if (!rstn) begin
        out <= 1'b1;
    end
end

endmodule