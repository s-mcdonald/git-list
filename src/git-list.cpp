
/******************************************************************************
 * MIT License
 * 
 * Copyright (c) 2025 Sam McDonald
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * provided to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * -----------------------------------------------------------------------------
 * 
 * Author: Sam McDonald
 * Date: 2025-02-22
 * 
 * Description:
 * 
 * This program will list all local branches similar to `git branch`
 * However it will also display the remote (if tracked), if the branch
 * has a current wip commit and its porcelain state.
 * 
 *****************************************************************************/

#include <iostream>
#include <iomanip>
#include <git2.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "git-branch_meta.h"
#include "gr-lib.h"
#include "io.h"
#include "gr-cli-options.h"

// Global variables for tracking memory usage
static size_t total_memory_allocated = 0;

void print_usage() {
    std::cout << "Usage: git list [options]\n"
              << "Options:\n"
              << "  -h, --help      Show this help message\n"
              << "  -w, --wip       Show WIP commits\n"
              << "  -s, --simple    Simple list display\n";
}

struct InputOptions {
    bool show_wip = false;
    bool simple_list_mode = false;
};

int main(int argc, char* argv[]) 
{
    struct InputOptions options;
    {
        // allocate on stack so we can pop it off
        GitReal::InputFlags iflags(argc, argv);
        options.simple_list_mode = iflags.has_flag("s");
        options.show_wip = iflags.has_flag("w");
    }

    const char * repo_path = "./";

    GitReal::Console console;
 
    if (git_libgit2_init() < 0) {
        std::cerr << "Failed to initialize libgit2" << std::endl;
        return -1;
    }

    git_repository *repo = nullptr;
    if (git_repository_open(&repo, repo_path) != 0) {
        git_libgit2_shutdown();
        return -1;        
    }

    // we have a repo, so lets create an iterator to see what we find ;)
    git_branch_iterator *iter = nullptr;
    if (git_branch_iterator_new(&iter, repo, GIT_BRANCH_LOCAL) != 0) {
        git_repository_free(repo);
        git_libgit2_shutdown();
        std::cerr << "Failed to create branch iterator." << std::endl;
        return -1;
    }

    {
        GitReal::BranchMetaInspector inspector(repo, iter);
        const auto branches = inspector.fetch_all_local_branch_meta(options.show_wip);
    
        if (true == options.simple_list_mode)
            console.print_simple_list(branches);
        else
            console << branches;
    }

    git_branch_iterator_free(iter);
    git_repository_free(repo);
}
