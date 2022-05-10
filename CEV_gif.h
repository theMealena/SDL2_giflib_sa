//**********************************************************/
//** Done by  |      Date     |  version |    comment     **/
//**------------------------------------------------------**/
//**   CEV    |    05-2016    |   1.0    |  creation/SDL2 **/
//**   CEV    |    05-2022    |   1.0    | doxy doc compliant**/
//**********************************************************/

#ifndef GIFUSER_H_INCLUDED
#define GIFUSER_H_INCLUDED

#include <SDL.h>

#define GIF_FORWARD     0
#define GIF_BACKWARD    1

#ifdef __cplusplus
extern "C" {
#endif


/** \brief Reading mode
 */
typedef enum GIF_MODE
{
    GIF_ALL        = -1,
    GIF_REPEAT_FOR = 0, /**< Loops forward */
    GIF_ONCE_FOR   = 1, /**< Plays forward once and stops */
    GIF_FORTH_BACK = 2, /**< Alternates forward/backward */
    GIF_REPEAT_REV = 3, /**< Loops backward */
    GIF_ONCE_REV   = 4, /**< Plays backward once and stops*/
    GIF_STOP       = 5  /**< Stops active animation*/
}
GIF_MODE;


/** \brief Gif method.
 */
typedef enum GIF_METHOD
{
    METHOD_OVERWRITE  = 1, /**< New frame superposes actual */
    METHOD_REDRAW     = 2  /**< Clears frame and redraw */
}
GIF_METHOD;


/** \brief Functions return values.
 */
enum
{
    GIF_FATAL   = -2,   /**< Fatal, unrecoverable error occurred, doom on its way... */
    GIF_ERR     = -1,   /**< Some error occured, still possible to find a way out */
    GIF_OK      = 0     /**< Everything is ok */
};


/** \brief Gif animation instance.
 */
typedef struct CEV_GifAnim CEV_GifAnim;


char CEV_gifReadWriteErr;/**< Any file r/w error occurred */


/** \brief Loads gif file.
 *
 * \param fileName : file to open.
 * \param renderer : SDL_Renderer* animation will be related to.
 *
 * \return CEV_GifAnim* on success , NULL on error.
 */
CEV_GifAnim * CEV_gifAnimLoad(const char* fileName, SDL_Renderer *renderer);


/** \brief Loads gif file from SDL_RWops.
 *
 * \param rwops : SDL_RWops* to load gif from.
 * \param renderer : SDL_Renderer* animation will be related to.
 * \param freeSrc : internally closes SDL_RWops if not 0.
 *
 * \return CEV_GifAnim* on success, NULL on error.
 */
CEV_GifAnim * CEV_gifAnimLoadRW(SDL_RWops* rwops, SDL_Renderer *renderer, char freeSrc);


/** \brief Fetches gif comment.
 *
 * \param anim : CEV_GifAnim* to extract comment from.
 *
 * \return char* on comment if some, NULL otherwise.
 */
char *CEV_gifComment(CEV_GifAnim *anim);



/** \brief Fetches gif version.
 *
 * \param anim : CEV_GifAnim* to extract version from.
 *
 * \return char* on version if any, on nul char '\0' otherwise.
 */
char *CEV_gifVersion(CEV_GifAnim *anim);


/** \brief Fetches gif signature.
 *
 * \param anim : CEV_GifAnim* to extract version from.
 *
 * \return char* on signature if any, on nul char '\0' otherwise.
 */
char *CEV_gifSignature(CEV_GifAnim *anim);


/** \brief Fetches user's texture.
 *
 * \param anim : CEV_GifAnim* to get texture from.
 *
 * \return SDL_Texture* for user's end.
 */
SDL_Texture *CEV_gifTexture(CEV_GifAnim *anim);


/** \brief Fetches number of frames.
 *
 * \param anim : CEV_GifAnim* to get info from.
 *
 * \return number of pictures.
 */
int CEV_gifFrameNum(CEV_GifAnim *anim);


/** \brief Forces skip to next frame.
 *
 * \param anim : CEV_GifAnim* to modify.
 *
 * \return N/A.
 */
void CEV_gifFrameNext(CEV_GifAnim *anim);


/** \brief Sets animation speed.
 *
 * \param anim : CEV_GifAnim* to modify.
 * \param index : frame index or GIF_ALL to change all frames.
 * \param timeMs : time to apply in milliseconds.
 *
 * \return N/A.
 */
void CEV_gifTimeSet(CEV_GifAnim *anim, unsigned int index, uint16_t timeMs);


/** \brief Sets loop reading mode.
 *
 * \param anim : CEV_GifAnim* to modify.
 * \param loopMode : read mode to apply.
 *
 * \return N/A.
 *
 * \sa GIF_MODE
 */
void CEV_gifLoopMode(CEV_GifAnim *anim, unsigned int loopMode);


/** \brief Resets loop animation.
 *
 * \param anim : CEV_GifAnim* to modify.
 *
 * \return N/A.
 */
void CEV_gifLoopReset(CEV_GifAnim *anim);


/** \brief Updates animation.
 *
 * \param anim : CEV_GifAnim* to animate.
 *
 * \return 1 at frame change, 0 otherwise.
 */
char CEV_gifAnimAuto(CEV_GifAnim *anim);


/** \brief Reverses play mode.
 *
 * \param anim CEV_GifAnim* to modify.
 *
 * \return N/A.
 */
void CEV_gifReverse(CEV_GifAnim *anim);


/** \brief Frees animation structure content and itself.
 *
 * \param anim : CEV_GifAnim* to free.
 *
 * \return N/A.
 */
void CEV_gifAnimFree(CEV_GifAnim *anim);


/** \brief Queries loop status.
 *
 * \param anim : CEV_GifAnim* to check.
 *
 * \return 1 if playing, 0 if animation has ended.
 */
char CEV_gifLoopStatus(CEV_GifAnim *anim);


/** \brief Queries display method.
 *
 * \param anim : CEV_GifAnim* to query.
 * \param index : frame to query.
 *
 * \return frame method.
 *
 * \sa GIF_METHOD
 */
char CEV_gifMethod(CEV_GifAnim* anim, unsigned int index);


/** \brief Sets display method.
 *
 * \param anim : CEV_GifAnim* to modify.
 * \param index : frame to modify or GIF_ALL for all frames.
 * \param method : method to apply.
 *
 * \return N/A.
 *
 * \sa GIF_METHOD
 */
void CEV_gifMethodSet(CEV_GifAnim* anim, int index, uint8_t method);

#ifdef __cplusplus
}
#endif

#endif // GIFUSER_H_INCLUDED
