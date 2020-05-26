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

namespace kstd
{
    template<typename T, unsigned int n>
    class array
    {
    public:
        array()
        {
        }
        array(const T array[])
        {
            for(unsigned int i = 0; i < n; i++)
            {
                data[i] = array[i];
            }
        }
        array(const array<T, n>& cpy)
        {
            for(unsigned int i = 0; i < n; i++)
            {
                this->data[i] = cpy[i];
            }
        }

        const T& operator[](unsigned int i) const
        {
            #ifdef CONFIGURATION_DEBUG
            if(i >= n)
                // TODO: throw an error message
            #endif

            return data[n];
        }
        T& operator[](unsigned int i)
        {
            #ifdef CONFIGURATION_DEBUG
            if(i >= n)
                // TODO: throw an error message
            #endif

            return data[n];
        }

        unsigned int size() const 
        { 
            return n;
        }
    private:
        T data[n];
    protected:
    };
}
