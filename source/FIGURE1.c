/* This function will track the splitbar in details view using the
 * keyboard.  This function could be called as a result of a menu
 * item selected by the user. */
VOID TrackSplitbar (HWND hwndCnr)
{
 TRACKINFO  ti;
 RECTL      rclDV, rclCnr, rclCnrTitle;
 CNRINFO    CnrInfo;

 /* Query the CnrInfo structure from the container.  From it we will
  * get the current position of the splitbar. */
 WinSendMsg (hwndCnr, CM_QUERYCNRINFO,
             MPFROMP(&CnrInfo), MPFROMSHORT(sizeof(CNRINFO)));

 /* Get the window rectangles for the container title window, the left
  * details view window, and the container window itself. */
 WinQueryWindowRect (WinWindowFromID (hwndCnr, CID_CNRTITLEWND), &rclCnrTitle);
 WinQueryWindowRect (WinWindowFromID (hwndCnr, CID_LEFTDVWND), &rclDV);
 WinQueryWindowRect (hwndCnr, &rclCnr);

 /* Initialize the TrackInfo structure.  The splitbar has the width of
  * a SizeBorder, and has the height of the container window minus the
  * container title window. */
 ti.cxBorder = (SHORT)WinQuerySysValue (HWND_DESKTOP, SV_CXSIZEBORDER);
 ti.cyBorder = (SHORT)(rclCnr.yTop - rclCnrTitle.yTop);
 ti.cxGrid   = (SHORT)rclCnr.xRight;
 ti.cyGrid   = (SHORT)rclCnr.yTop;

 /* Set the x Keyboard increment to be the number of pels you want the
  * splitbar to move when the user presses the right and left arrow
  * keys.  Set the y Keyboard increment to 0. */
 ti.cxKeyboard = 10;
 ti.cyKeyboard = 0;

 /* Set up the rectangle that is to be tracked.  This is the rectangle
  * of the splitbar. */
 ti.rclTrack.xLeft   = CnrInfo.xVertSplitbar;
 ti.rclTrack.xRight  = ti.rclTrack.xLeft + ti.cxBorder;
 ti.rclTrack.yBottom = rclCnr.yBottom;
 ti.rclTrack.yTop    = ti.cyBorder;

 /* Set up the absolute boundary rectangle.  This is the rectangle
  * specifying the boundary which the tracking rectangle cannot exceed.
  * Set it to be the left, right, and bottom of the container, and the
  * top of the splitbar. */
 ti.rclBoundary.xLeft   = rclCnr.xLeft;
 ti.rclBoundary.xRight  = rclCnr.xRight;
 ti.rclBoundary.yBottom = rclCnr.yBottom;
 ti.rclBoundary.yTop    = ti.cyBorder;
 ti.ptlMinTrackSize.x   = ti.cxBorder;
 ti.ptlMinTrackSize.y   = ti.cyBorder;
 ti.ptlMaxTrackSize.x   = ti.cxBorder;
 ti.ptlMaxTrackSize.y   = ti.cyBorder;

 /* Set the track flags.  TF_SETPOINTERPOS will put the mouse pointer
  * in the middle of the tracking rectangle (splitbar). */
 ti.fs = TF_MOVE | TF_ALLINBOUNDARY | TF_SETPOINTERPOS;

 /* If the tracking is successful, inform the container of the new
  * splitbar position. */
 if (WinTrackRect (hwndCnr, NULL, &ti))
 {
   /* Inform the container of the new splitbar position. */
   CnrInfo.xVertSplitbar = ti.rclTrack.xLeft;
   WinSendMsg (hwndCnr, CM_SETCNRINFO,
               &CnrInfo, MPFROMLONG(CMA_XVERTSPLITBAR));
 }
 return;
}
