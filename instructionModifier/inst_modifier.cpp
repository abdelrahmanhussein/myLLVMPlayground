#include "llvm/Passes/PassBuilder.h"
#include "llvm/Plugins/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"



using namespace llvm;

void modifyInstruction(Function &F)
{
    for (auto &BB : F)
    {
        for (auto I_it = BB.begin(), I_end = BB.end(); I_it != I_end;)
        {
            Instruction &I = *I_it;
            *I_it++; // Increment the iterator before modifying the instruction
            // llvm::outs() << "Instruction: " << I << " has " << I.getNumOperands() << " operands\n";
                if (I.getOpcode() == llvm::Instruction::Mul)
                {
                    llvm::IRBuilder<> Builder(&I);
                    // llvm::Value *NewInst = Builder.CreateOr(I.getOperand(0), I.getOperand(1));
                    llvm::Instruction *NewInst = llvm::BinaryOperator::CreateAdd(I.getOperand(0), I.getOperand(1), "addtmp");
                    Builder.Insert(NewInst);
                    I.replaceAllUsesWith(NewInst);
                    I.eraseFromParent();
                }
                // llvm::ConstantInt *CI = llvm::dyn_cast<llvm::ConstantInt>(op);
                // if (CI && CI->getZExtValue() == 0xdead)
                // {
                //     llvm::Value *NewValue = llvm::ConstantInt::get(op->getType(), 0xbbbb);
                //     op.set(NewValue);
                // }
            
        }
    }
}

struct instructionModifier : PassInfoMixin<instructionModifier>
{
    // Main entry point, takes IR unit to run the pass on (&F) and the
    // corresponding pass manager (to be queried if need be)
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &)
    {
        for (auto &F : M)
        {
            if (!F.empty())
            {
                modifyInstruction(F);
            }
        }
        return PreservedAnalyses::all();
    }

    // Without isRequired returning true, this pass will be skipped for functions
    // decorated with the optnone LLVM attribute. Note that clang -O0 decorates
    // all functions with optnone.
    static bool isRequired() { return true; }
};
// namespace

llvm::PassPluginLibraryInfo getinstructionModifierPluginInfo()
{
    return {LLVM_PLUGIN_API_VERSION, "instructionModifier", LLVM_VERSION_STRING,
            [](PassBuilder &PB)
            {
                PB.registerPipelineParsingCallback(
                    [](StringRef Name, ModulePassManager &FPM,
                       ArrayRef<PassBuilder::PipelineElement>)
                    {
                        if (Name == "instructionModifier")
                        {
                            FPM.addPass(instructionModifier());
                            return true;
                        }
                        return false;
                    });
            }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo()
{
    return getinstructionModifierPluginInfo();
}