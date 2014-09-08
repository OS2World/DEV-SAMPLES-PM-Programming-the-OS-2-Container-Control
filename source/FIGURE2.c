/* This function is used to bring a particular record in the container
 * to the viewport.  It attempts to place the record as close to the
 * top left corner as possible. */
VOID ScrollToRecord (HWND hwndCnr, PRECORDCORE pRecord)
{
  RECTL             rclViewport, rclItem;
  QUERYRECORDRECT   QueryRecordRect;
  LONG              lMargin = 4L;
  CNRINFO           CnrInfo;

  /* Query the container for the current view.  If a text view is the
   * current view, then CMA_ICON is invalid for QueryRecordRect.fsExtent */
  WinSendMsg (hwndCnr, CM_QUERYCNRINFO,
              MPFROMP(&CnrInfo), MPFROMSHORT(sizeof(CNRINFO)));

  /* Query the container for the position of the record relative
   * to the viewport.  We want the rectangle containing both the icon
   * and the text of the record. */
  QueryRecordRect.cb       = sizeof(QUERYRECORDRECT);
  QueryRecordRect.pRecord  = pRecord;
  QueryRecordRect.fsExtent = CMA_ICON | CMA_TEXT;
  QueryRecordRect.fRightSplitWindow = FALSE;
  if (CnrInfo.flWindowAttr & CV_TEXT)
    QueryRecordRect.fsExtent = CMA_TEXT;
  else
    QueryRecordRect.fsExtent = CMA_ICON | CMA_TEXT;

  WinSendMsg (hwndCnr, CM_QUERYRECORDRECT,
              MPFROMP(&rclItem), MPFROMP(&QueryRecordRect));

  /* Query the container for the size of the current viewport.
   * This is necessary because the position of the record
   * is relative to the bottom left corner of the viewport. */
  WinSendMsg (hwndCnr, CM_QUERYVIEWPORTRECT,
              MPFROMP(&rclViewport), MPFROM2SHORT(CMA_WINDOW, FALSE));

  /*  Scroll the container vertically to bring the record to a position
   *  just below the top of the viewport. */
  WinSendMsg (hwndCnr, CM_SCROLLWINDOW, MPFROMSHORT(CMA_VERTICAL),
              MPFROMLONG(rclViewport.yTop - rclItem.yTop - lMargin));

  /*  Scroll the container horizontally to bring the record to a
   *  position just to the right of the left edge of the viewport. */
  WinSendMsg (hwndCnr, CM_SCROLLWINDOW, MPFROMSHORT(CMA_HORIZONTAL),
              MPFROMLONG(rclItem.xLeft - lMargin));
  return;
}
