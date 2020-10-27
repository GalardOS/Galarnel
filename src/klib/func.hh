/*
 * This project is provided under the GNU GPL v2 license, more information can 
 * found on https://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    - Iker Galardi
 */

#pragma once

#include <klib/printf.hh>

namespace kstd {
    
    template<typename T> 
    class func {
    public:
        func() : function_pointer(nullptr) {}
        func(T* function_pointer) : function_pointer(function_pointer) {}

        T* operator&() const {
            return function_pointer;
        }

        T* ptr() const {
            return function_pointer;
        }

        template<typename... vargs>
        auto execute(vargs... args) const {
            if(!function_pointer) {
                /// TODO: dont execute and return nothing (default constructed return of function??)
                kstd::printf("[E] Tried to call null function\r\n");
            }
            return function_pointer(args...);
        }

        static func<T> null() {
            return func();
        }
    private:
        T* function_pointer;
    protected:
    };


}
