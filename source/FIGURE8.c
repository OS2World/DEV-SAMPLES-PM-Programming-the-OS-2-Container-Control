/* This function will allocate a record and insert it into the 3
 * container windows passed in.  After allocating the record, 3 unique
 * (x,y) positions will be assigned, as well as 2 sets of unique
 * attributes. */
BOOL AllocateAndInsertRecord(HWND hwndCnr1, HWND hwndCnr2,
                             HWND hwndCnr3, HPOINTER hIcon,
                             PSZ pszIconText, RECORDINSERT RecordInsert)
{
 PMINIRECORDCORE  pRecord;
 LONG             rc = 0;

 /* Allocate one MINIRECORDCORE structure from the first container.
  * Do not allocate any addition bytes of storage. */
 pRecord = (PMINRECORDCORE)WinSendMsg (hwndCnr1, CM_ALLOCRECORD,
                                       MPFROMLONG(0), MPFROMSHORT(1));

 /* If we don't get a record, bail out now. */
 if (pRecord)
 {
   /* Fill in the record memory with the initial information. */
   pRecord->cb           = sizeof(MINIRECORDCORE);
   pRecord->hptrIcon     = hIcon;
   pRecord->ptlIcon.x    = 100;
   pRecord->ptlIcon.y    = 100;
   pRecord->flRecordAttr = CRA_SELECTED | CRA_RECORDREADONLY;
   pRecord->pszIcon = malloc (TEXT_SIZE);
   strcpy (pRecord->pszIcon, pszIconText);

   /* Insert the record into the first container. */
   rc = (LONG)WinSendMsg (hwndCnr1, CM_INSERTRECORD,
                          MPFROMP(pRecord), MPFROMP(&RecordInsert));

   if (rc)
   {
     /* Change the (x,y) position of the record, and insert the same
      * record into the second container. */
     pRecord->ptlIcon.x += 50;
     pRecord->ptlIcon.y -= 30;

     rc = (LONG)WinSendMsg (hwndCnr2, CM_INSERTRECORD,
                            MPFROMP(pRecord), MPFROMP(&RecordInsert));
   }

   if (rc)
   {
     /* Change the (x,y) position again, and turn the selection
      * attribute off of the same record and insert it into the
      * third container.  If all is successful, return TRUE,
      * otherwise return FALSE. */
     pRecord->ptlIcon.x = 275;
     pRecord->ptlIcon.y = pRecord->ptlIcon.x + 40;
     pRecord->flRecordAttr &= ~CRA_SELECTED;

     rc = (LONG)WinSendMsg (hwndCnr3, CM_INSERTRECORD,
                            MPFROMP(pRecord), MPFROMP(&RecordInsert));
   }
 }
 /* Convert rc to BOOL and return. */
 return !!rc;
}
