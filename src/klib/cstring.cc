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

#include "cstring.hh"

namespace kstd
{
    char* strcat(char* dest, const char* src)
    {
        unsigned int srcLength = strlen(src);
        return strncat(dest, src, srcLength);
    }

    char* strncat(char* dest, const char* src, unsigned int n)
    {
        unsigned int lastCharIndex = strlen(dest);
        for(unsigned int i = 0; i < n; i++)
            dest[lastCharIndex + i] = src[i];
        dest[lastCharIndex + n] = '\0';
        return dest;
    }

    bool strcmp(const char* str1, const char* str2)
    {
        unsigned int str1Length = strlen(str1);
        unsigned int str2Length = strlen(str2);
        if(str1Length != str2Length)
            return false;

        for(unsigned int i = 0; i < str1Length; i++)
            if(str1[i] != str2[i])
                return false;

        return true;
    }

    char* strcpy(char* dest, const char* src)
    {
        unsigned int srcLength = strlen(src);
        return strncpy(dest, src, srcLength);
    }

    char* strncpy(char* dest, const char* src, unsigned int n)
    {
        for(unsigned int i = 0; i < n; i++)
            dest[i] = src[i];
        return dest;
    }

    unsigned int strlen(const char* str)
    {
        unsigned int i = 1;
        while(str[i] != '\0')
            i++;
        return i;
    }
}

