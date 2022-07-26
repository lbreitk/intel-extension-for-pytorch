#pragma once

#include <torch/csrc/jit/ir/ir.h>
#include <torch/csrc/jit/ir/irparser.h>
#include <torch/csrc/jit/ir/subgraph_matcher.h>
#include <torch/csrc/jit/passes/constant_propagation.h>
#include <torch/csrc/jit/passes/dead_code_elimination.h>
#include <torch/csrc/jit/passes/subgraph_rewrite.h>

namespace torch_ipex {
namespace jit {
namespace graph_rewrite {

void FuseShuffle(std::shared_ptr<torch::jit::Graph>& graph);
void FuseMHAScoreCalc(std::shared_ptr<torch::jit::Graph>& graph);
void FuseLinearSwishCustomized(std::shared_ptr<torch::jit::Graph>& graph);
void replaceAtenMaxPool2dWithIpexMaxPool2d(
    std::shared_ptr<torch::jit::Graph>& graph);
void fuseBmmAdd(std::shared_ptr<torch::jit::Graph>& graph);

void replaceOpsWithAtenInplaceOps(std::shared_ptr<torch::jit::Graph>& graph);
void replaceAtenOpsWithIpexInplaceOps(
    std::shared_ptr<torch::jit::Graph>& graph);
void replaceAtenSoftmaxWithIpexSoftmax(
    std::shared_ptr<torch::jit::Graph>& graph);
void replaceAtenBatchNormWithIpexBatchNorm(
    std::shared_ptr<torch::jit::Graph>& graph);
void replaceAtenLayerNormWithIpexLayerNorm(
    std::shared_ptr<torch::jit::Graph>& graph);
void replaceEmbeddingBagWithQEmbeddingBag(
    std::shared_ptr<torch::jit::Graph>& graph);
void replaceInteractionWithQInteraction(
    std::shared_ptr<torch::jit::Graph>& graph);
void preprocessSizeForQLstm(std::shared_ptr<torch::jit::Graph>& graph);
void replaceLstmWithQLstm(std::shared_ptr<torch::jit::Graph>& graph);

void replaceFrozenIPEXConvWithAtenConv(
    std::shared_ptr<torch::jit::Graph>& graph);
void replaceFrozenIPEXLinearWithAtenLinear(
    std::shared_ptr<torch::jit::Graph>& graph);
void insertPrePackedConvOp(std::shared_ptr<torch::jit::Graph>& graph);
void fuseConvWithEltwise(std::shared_ptr<torch::jit::Graph>& graph);
void fuseConvAddRelu(std::shared_ptr<torch::jit::Graph>& graph);
void fuseBottleneck(std::shared_ptr<torch::jit::Graph>& graph);

// This graph pass is to replace at::hardsigmoid with IPEX hardsigmoid.
// Because NNC pulls aten::hardsigmoidn into its fusion group while its
// performance might not be good engouh if the mout outer loop is small. Besides
// that, IPEX will use oneDNN post-op to fuse hard sigmoid. Hence, this graph
// pass is a workaround for this release and will be removed in the next major
// release.
void ReplaceHardsigmoidWithIPEX(std::shared_ptr<torch::jit::Graph>& graph);

void RecordAtenLinearNodes(
    std::shared_ptr<torch::jit::Graph>& graph,
    std::unordered_set<torch::jit::Node*>& aten_linear);
void insertPrePackedLinearOp(
    std::shared_ptr<torch::jit::Graph>& graph,
    std::unordered_set<torch::jit::Node*>& aten_linear);
void fuseLinearWithEltwise(std::shared_ptr<torch::jit::Graph>& graph);
void fuseLinearAddRelu(std::shared_ptr<torch::jit::Graph>& graph);

void FuseAddLayerNorm(std::shared_ptr<torch::jit::Graph>& graph);
void FuseMatmulDiv(std::shared_ptr<torch::jit::Graph>& graph);
void FuseConcatBnRelu(std::shared_ptr<torch::jit::Graph>& graph);

void insertPrePackedConvTransposeOp(std::shared_ptr<torch::jit::Graph>& graph);
void fuseConvTransposeWithEltwise(std::shared_ptr<torch::jit::Graph>& graph);
void fuseConvTransposeAdd(std::shared_ptr<torch::jit::Graph>& graph);

void FusedEinsumPost(std::shared_ptr<torch::jit::Graph>& graph);

// This code will be removed after the official PyTorch NNC fully support
// BFloat16.
void replaceAtenToWithIPEXTo(std::shared_ptr<torch::jit::Graph>& graph);
void replaceIPEXToWithAtenTo(std::shared_ptr<torch::jit::Graph>& graph);

} // namespace graph_rewrite
} // namespace jit
} // namespace torch_ipex