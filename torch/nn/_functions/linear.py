import torch
<<<<<<< HEAD
from torch.autograd import Function
from torch.autograd import Variable


class Linear(Function):

    @staticmethod
    def forward(ctx, input, weight, bias=None):
        ctx.save_for_backward(input, weight, bias)
        output = input.new(input.size(0), weight.size(0))
        output.addmm_(0, 1, input, weight.t())
        if bias is not None:
            # cuBLAS doesn't support 0 strides in sger, so we can't use expand
            ctx.add_buffer = input.new(input.size(0)).fill_(1)
            output.addr_(ctx.add_buffer, bias)
        return output

    @staticmethod
    def backward(ctx, grad_output):
        input, weight, bias = ctx.saved_variables

        grad_input = grad_weight = grad_bias = None
        if ctx.needs_input_grad[0]:
            grad_input = torch.mm(grad_output, weight)
        if ctx.needs_input_grad[1]:
            grad_weight = torch.mm(grad_output.t(), input)
        if bias is not None and ctx.needs_input_grad[2]:
            grad_bias = torch.mv(grad_output.t(), Variable(ctx.add_buffer))

        if bias is not None:
            return grad_input, grad_weight, grad_bias
        else:
            return grad_input, grad_weight
=======
from torch.autograd import Function, Variable
>>>>>>> master


class Bilinear(Function):

    @staticmethod
    def forward(ctx, input1, input2, weight, bias=None):
        ctx.save_for_backward(input1, input2, weight, bias)

        output = input1.new(input1.size(0), weight.size(0))

        buff = input1.new()

        # compute output scores:
        for k, w in enumerate(weight):
            torch.mm(input1, w, out=buff)
            buff.mul_(input2)
            torch.sum(buff, 1, keepdim=True, out=output.narrow(1, k, 1))

        if bias is not None:
            output.add_(bias.expand_as(output))

        return output

    @staticmethod
    def backward(ctx, grad_output):
        input1, input2, weight, bias = ctx.saved_variables
        grad_input1 = grad_input2 = grad_weight = grad_bias = None

        buff = Variable(input1.data.new())

        if ctx.needs_input_grad[0] or ctx.needs_input_grad[1]:
            grad_input1 = torch.mm(input2, weight[0].t())
            grad_input1 = grad_input1.mul(grad_output.narrow(1, 0, 1).expand(grad_input1.size()))
            grad_input2 = torch.mm(input1, weight[0])
            grad_input2 = grad_input2.mul(grad_output.narrow(1, 0, 1).expand(grad_input2.size()))

            for k in range(1, weight.size(0)):
                buff = input2.mm(weight[k].t())
                buff = buff.mul(grad_output.narrow(1, k, 1).expand(grad_input1.size()))
                grad_input1.add_(buff)

                buff = input1.mm(weight[k])
                buff = buff.mul(grad_output.narrow(1, k, 1).expand(grad_input2.size()))
                grad_input2.add_(buff)

        grad_weight = Variable(weight.data.new(weight.size()))
        if ctx.needs_input_grad[2]:
            # accumulate parameter gradients:
            for k in range(weight.size(0)):
                buff = input1.mul(grad_output.narrow(1, k, 1).expand_as(input1))
                grad_weight[k] = torch.mm(buff.t(), input2)

        if bias is not None and ctx.needs_input_grad[3]:
            grad_bias = grad_output.sum(0, keepdim=False)

        return grad_input1, grad_input2, grad_weight, grad_bias
