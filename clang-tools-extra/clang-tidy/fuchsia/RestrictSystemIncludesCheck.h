//===--- RestrictSystemIncludesCheck.h - clang-tidy---------- ----*- C++-*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_FUCHSIA_RESTRICTINCLUDESSCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_FUCHSIA_RESTRICTINCLUDESSCHECK_H

#include "../ClangTidy.h"
#include "../utils/OptionsUtils.h"

namespace clang {
namespace tidy {
namespace fuchsia {

/// Checks for allowed includes and suggests removal of any others. If no
/// includes are specified, the check will exit without issuing any warnings.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/fuchsia-restrict-system-includes.html
class RestrictSystemIncludesCheck : public ClangTidyCheck {
public:
  RestrictSystemIncludesCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context),
        AllowedIncludes(
            utils::options::parseStringList(Options.get("Includes", ""))) {}

  void registerPPCallbacks(CompilerInstance &Compiler) override;
  void storeOptions(ClangTidyOptions::OptionMap &Opts) override;
  const std::vector<std::string> &getAllowedIncludes() const {
    return AllowedIncludes;
  }

private:
  std::vector<std::string> AllowedIncludes;
};

} // namespace fuchsia
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_FUCHSIA_RESTRICTINCLUDESSCHECK_H
