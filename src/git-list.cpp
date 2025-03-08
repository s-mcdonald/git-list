
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
#include <new> // Required for std::bad_alloc
#include <iomanip>
#include <git2.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "gr-lib.h"
#include "io.h"
#include "gr-cli-options.h"
#include "git-repo-state.h"

// Global variables for tracking memory usage
static size_t s_total_memory_allocated = 0;
static int s_total_allocations = 0;
static int s_total_deallocations = 0;

#ifdef DEBUG

void* operator new(std::size_t n) {
    s_total_memory_allocated += n;
    void* p = std::malloc(n);
    if (!p) {
        std::cerr << "Memory allocation failed" << std::endl;
        std::exit(EXIT_FAILURE); 
    }
    s_total_allocations++;
    return p;
}

void operator delete(void* p) noexcept {
    std::free(p);
    s_total_deallocations++;
}

void print_memory_usage() {
    std::cout 
        << "Total memory : ( " 
        << s_total_allocations 
        << " / "
        << s_total_deallocations
        << " )" 
        << " Total memory allocated/deallocated respectivly with Bytes:  " 
        << s_total_memory_allocated
        << std::endl;
}
#else
void print_memory_usage() {}
#endif
constexpr void print_usage() {
    std::cout << "Usage: git list [options]\n"
              << "Options:\n"
              << "  -h, --help      Show this help message\n"
              << "  -w, --wip       Show WIP commits\n"
              << "  -s, --simple    Simple list display\n";
}

int main(int argc, char* argv[]) 
{
#ifdef DEBUG
    std::cout << "DEBUG MODE:" << std::endl;
    std::cout << "" << std::endl;
#endif

    struct InputOptions options;
    {
        GitReal::InputFlags iflags(argc, argv);
        options.show_wip = iflags.has_flag("w");
        options.show_worktrees = iflags.has_flag("a");
        options.simple_list_mode = iflags.has_flag("s");
        options.show_tracked = iflags.has_flag("t");
        options.show_help = iflags.has_flag("h");

        if(options.show_help) {
            print_usage();
            return 0;
        }
    }
 
    {
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
            const auto repo_info = GitReal::Analyze::get_repository_info(repo, iter);

            console.print_repo_info(repo_info, options);
        }

        git_branch_iterator_free(iter);
        git_repository_free(repo);
    }

#ifdef DEBUG
    print_memory_usage();
#endif
}
