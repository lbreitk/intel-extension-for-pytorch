import torch
from torch.testing._internal.common_utils import TestCase

import intel_extension_for_pytorch

import pytest

dpcpp_device = torch.device("xpu")
cpu_device = torch.device("cpu")


class TestTorchMethod(TestCase):
    def test_conv_tbc(self, dtype=torch.float):

        input_cpu = torch.randn(3, 4, 5)
        weight_cpu = torch.randn(3, 5, 4)
        bias_cpu = torch.randn(4)

        input_sycl = input_cpu.to("xpu")
        weight_sycl = weight_cpu.to("xpu")
        bias_sycl = bias_cpu.to("xpu")

        m = torch.conv_tbc

        print("cpu")
        input_cpu.requires_grad = True
        output_cpu = m(input_cpu, weight_cpu, bias_cpu)
        print("output: ", output_cpu)
        output_cpu.backward(torch.ones_like(output_cpu))
        print("input.grad: ", input_cpu.grad)
        # input_cpu.grad.zero_()

        print("sycl")
        input_sycl.requires_grad = True
        output_sycl = m(input_sycl, weight_sycl, bias_sycl)
        print("output: ", output_sycl.cpu())
        output_sycl.backward(torch.ones_like(output_sycl).to("xpu"))
        print("input.grad: ", input_sycl.grad)
        # input_sycl.grad.zero_()

        self.assertEqual(output_cpu, output_sycl.cpu())
        self.assertEqual(input_cpu.grad, input_sycl.grad.cpu())