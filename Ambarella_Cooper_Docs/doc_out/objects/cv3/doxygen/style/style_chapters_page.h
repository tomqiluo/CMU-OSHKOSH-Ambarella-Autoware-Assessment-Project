/*!
 * @file doc_doxygen_style_guide.h
 * @brief document for doxygen style guide
 * @version 0.1
 * @date 2022-10-10
 *
 * @copyright Copyright (c) 2024 Ambarella International LP.
 *
 * This file and its contents ("Software") are protected by intellectual
 * property rights including, without limitation, U.S. and/or foreign
 * copyrights. This Software is also the confidential and proprietary
 * information of Ambarella International LP and its licensors. You may not use, reproduce,
 * disclose, distribute, modify, or otherwise prepare derivative works of this
 * Software or any portion thereof except pursuant to a signed license agreement
 * or nondisclosure agreement with Ambarella International LP or its authorized affiliates.
 * In the absence of such an agreement, you agree to promptly notify and return
 * this Software to Ambarella International LP.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF NON-INFRINGEMENT,
 * MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL AMBARELLA INTERNATIONAL LP OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; COMPUTER FAILURE OR MALFUNCTION; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*!
 * @page doc_style_guide Doxygen Style Guide
 * The following is a list of the typographical conventions used in Doxygen document.
 *
 * @section doc_style_section 1. Section Index
 * @subsection doc_style_section_example 1.1 Webpage Example
 * @image html doc_style_section_example.png width=30%
 *
 * @subsection doc_style_section_syntax 1.2 Doxygen Syntax
 * @image html doc_style_section_syntax.png width=30%
 *
 * - - - -
 *
 * @section doc_style_heading 2. Heading
 * @subsection doc_style_heading_example 2.1 Webpage Example
 * @image html doc_style_heading_example.png width=30%
 *
 * @subsection doc_style_heading_syntax 2.2 Doxygen Syntax
 * @image html doc_style_heading_syntax.png width=40%
 * @note
 * The first letter of the heading text is capitalized.
 *
 * - - - -
 *
 * @section doc_style_names 3. Software Name / Library Name / Framework Name
 * @subsection doc_style_names_example 3.1 Webpage Example
 * @image html doc_style_names_example.png width=30%
 *
 * @subsection doc_style_names_syntax 3.2 Doxygen Syntax
 * @image html doc_style_names_syntax.png width=30%
 *
 * - - - -
 *
 * @section doc_style_num_list 4. Number List
 * @subsection doc_style_num_list_example 4.1 Webpage Example
 * @image html doc_style_num_list_example.png width=60%
 *
 * @subsection doc_style_num_list_syntax 4.2 Doxygen Syntax
 * @image html doc_style_num_list_syntax.png width=60%
 * @note
 * The number list is used to describe the operations and procedures for user.
 *
 * - - - -
 *
 * @section doc_style_bullet_list 5. Bullet List
 * @subsection doc_style_bullet_list_example 5.1 Webpage Example
 * @image html doc_style_bullet_list_example.png width=40%
 *
 * @subsection doc_style_bullet_list_syntax 5.2 Doxygen Syntax
 * @image html doc_style_bullet_list_syntax.png width=40%
 *
 * - - - -
 *
 * @section doc_style_title 6. Document Title
 * @subsection doc_style_title_example 6.1 Webpage Example
 * @image html doc_style_title_example.png width=40%
 *
 * @subsection doc_style_title_syntax 6.2 Doxygen Syntax
 * @image html doc_style_title_syntax.png width=40%
 * @note
 * The referred document is in Word form. For referred documents in Doxygen,
 * use the reference link style below.
 *
 * - - - -
 *
 * @section doc_style_path 7. Folder Path / File Name / Unit Test Program
 * @subsection doc_style_path_example 7.1 Webpage Example
 * @image html doc_style_path_example.png width=40%
 *
 * @subsection doc_style_path_syntax 7.2 Doxygen Syntax
 * @image html doc_style_path_syntax.png width=40%
 *
 * - - - -
 *
 * @section doc_style_ref_link 8. Reference Link
 * @subsection doc_style_ref_link_example 8.1 Webpage Example
 * @image html doc_style_ref_link_example.png width=40%
 *
 * @subsection doc_style_ref_link_syntax 8.2 Doxygen Syntax
 * @image html doc_style_ref_link_syntax.png width=40%
 * @note
 * "<ref_id>" can be section id (or subsection-id, subsubsection-id), or table
 * caption, or image caption.
 *
 * - - - -
 *
 * @section doc_style_code 9. Linux Command / C Code Excerpt / Shell Script
 * @subsection doc_style_code_example 9.1 Webpage Example
 * @image html doc_style_code_example.png width=40%
 *
 * @subsection doc_style_code_syntax 9.2 Doxygen Syntax
 * @image html doc_style_code_syntax.png width=40%
 *
 * - - - -
 *
 * @section doc_style_example 10. Example
 * @subsection doc_style_example_example 10.1 Webpage Example
 * @image html doc_style_example_example.png width=60%
 *
 * @subsection doc_style_example_syntax 10.2 Doxygen Syntax
 * @image html doc_style_example_syntax.png width=60%
 *
 * - - - -
 *
 * @section doc_style_table 11. Table Caption
 * @subsection doc_style_table_example 11.1 Webpage Example
 * @image html doc_style_table_example.png width=60%
 *
 * @subsection doc_style_table_syntax 11.2 Doxygen Syntax
 * @image html doc_style_table_syntax.png width=60%
 * @note
 * - The first No."2" refers to chapter number, and the second "1" refers to
 *   caption index number.
 * - The first letter of caption text is capitalized and ends with a period.
 *
 * - - - -
 *
 * @section doc_style_image 12. Image Caption
 * @subsection doc_style_image_example 12.1 Webpage Example
 * @image html doc_style_image_example.png width=60%
 *
 * @subsection doc_style_image_syntax 12.2 Doxygen Syntax
 * @image html doc_style_image_syntax.png width=60%
 * @note
 * - The first "1" refers to chapter number, and the second "6" refers to
 *   caption index number.
 * - The first letter of caption text is capitalized and ends with a period.
 *
 * - - - -
 *
 * @section doc_style_faq 13. FAQ
 * @subsection doc_style_faq_example 13.1 Webpage Example
 * @image html doc_style_faq_example.png width=60%
 *
 * @subsection doc_style_faq_syntax 13.2 Doxygen Syntax
 * @image html doc_style_faq_syntax.png width=60%
 *
 * - - - -
 *
 * @section doc_style_note 14. Note
 * @subsection doc_style_note_example 14.1 Webpage Example
 * @image html doc_style_note_example.png width=40%
 *
 * @subsection doc_style_note_syntax 14.2 Doxygen Syntax
 * @image html doc_style_note_syntax.png width=30%
 *
 */
