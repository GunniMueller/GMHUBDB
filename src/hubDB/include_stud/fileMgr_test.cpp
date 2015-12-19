#include <fileMgr.h>

int FileMgr::test(bool details)
{
  FileMgr mgr(8);
  FileNo no[10], err_no,unused(100);
  BlockBuffer block(1),
			  block2(25),
			  block3(3),
			  r_block(3),
			  r_block2(25),
			  r_block3(1);
  // Test 1.1

  if (details)cout << "- ERROR: Block in nicht vorhandene Datei schreiben: " << endl;
  try{
	BlockBuffer err_block(10);
	mgr.write(unused, err_block);
    FAILED(cout);
  }catch(ErrorObj e){
    OKAY(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 1.2

  if (details)cout << "- ERROR: Block aus nicht vorhandener Datei lesen: " << endl;
  try{
	BlockBuffer err_block(1);
	mgr.read(unused, err_block);
    FAILED(cout);
  }catch(ErrorObj e){
    OKAY(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 2.1

  if (details)cout << "- Dateien 'test.dat' bis 'test7.dat' anlegen und öffnen: " << endl;
  try{
    mgr.create("test.dat", no[0]);
    mgr.create("test1.dat", no[1]);
    mgr.create("test2.dat", no[2]);
    mgr.create("test3.dat", no[3]);
    mgr.create("test4.dat", no[4]);
    mgr.create("test5.dat", no[5]);
    mgr.create("test6.dat", no[6]);
    mgr.create("test7.dat", no[7]);
    OKAY(cout);
  }catch(ErrorObj e){
    FAILED(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  bool flag=true;
  while(flag){
    flag=false;
    for(int i=0;i<8;++i){
      if(no[i]==unused){
	flag=true;
	++unused;
      }
    }
  }

  // Test 2.2

  if (details)cout << "- ERROR: Datei 'test8.dat' anlegen und öffnen: " << endl;
  try{
    mgr.create("test8.dat", err_no);
    FAILED(cout);
  }catch(ErrorObj e){
    OKAY(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 2.3

  if (details)cout << "- ERROR: Datei 'test8.dat' öffnen: " << endl;
  try{
    mgr.open("test8.dat", err_no);
    FAILED(cout);
  }catch(ErrorObj e){
    OKAY(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 2.4

  if (details)cout << "- ERROR: Datei 'test.dat' erneut anlegen und öffnen: " << endl;
  try{
    mgr.create("test.dat",err_no);
    FAILED(cout);
  }catch(ErrorObj e){
    OKAY(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 3

  if (details) cout << "- Datei 'test.dat' nochmals oeffnen: " << endl;
  FileNo test;
  try{
    mgr.open("test.dat", test);

  }catch(ErrorObj e){
    FAILED(cout);
  }
  if (test != no[0]) FAILED(cout);
  else OKAY(cout);
  if (details) cout << "-> " << mgr << endl;


  // Test 4.1

  if (details) cout << "- Block 1 in der Datei 'test.dat' schreiben: " << endl;
  strcpy(block.getBlockPtr(), "- Block 1 -");
  try{
    mgr.write(no[0], block);
    OKAY(cout);
  }catch(ErrorObj e){
    FAILED(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 4.2

  if (details) cout << "- Block 25 in der Datei 'test1.dat' schreiben: " << endl;
  strcpy(block2.getBlockPtr(), "------------------------- Test -------------------------");
  try{
    mgr.write(no[1], block2);
    OKAY(cout);
  }catch(ErrorObj e){
    FAILED(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 4.3

  if (details) cout << "- Block 3 in der Datei 'test.dat' schreiben: " << endl;
  strcpy(block3.getBlockPtr(), "--- Block 3 ---");
  try{
    mgr.write(no[0], block3);
    OKAY(cout);
  }catch(ErrorObj e){
    FAILED(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 4.4

  if (details) cout << "- ERROR: Block in eine nicht vorhandene Datei schreiben: " << endl;
  try{
    BlockBuffer err_block(33);
	mgr.write(unused, err_block);
    FAILED(cout);
  }catch(ErrorObj e){
    OKAY(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 5.1

  if (details) cout << "- Block 3 aus der Datei 'test.dat' lesen: " << endl;
  try { mgr.read(no[0], r_block); }
  catch(ErrorObj e){ FAILED(cout); }
  if (details) cout << "  Blockinhalt: \""
	                << r_block.getBlockPtr()
					<< "\""
					<< endl;
  if (strcmp(r_block.getBlockPtr(), "--- Block 3 ---")!=0) FAILED(cout);
  else OKAY(cout);
  if (details) cout << "-> " << mgr << endl;

  // Test 5.2

  if (details) cout << "- Block 25 aus der Datei 'test1.dat' lesen: " << endl;

  try { mgr.read(no[1], r_block2); }
  catch(ErrorObj e){ FAILED(cout); }
  if (details) cout << "  Blockinhalt: \""
	                << r_block2.getBlockPtr()
					<< "\""
					<< endl;
  if (strcmp(r_block2.getBlockPtr(), "------------------------- Test -------------------------")!=0) FAILED(cout);
  else OKAY(cout);
  if (details) cout << "-> " << mgr << endl;

  // Test 6

  if (details) cout << "- Dateien 'test.dat' bis 'test5.dat' schliessen: " << endl;
  try{
    mgr.close(no[0]);
    mgr.close(no[1]);
    mgr.close(no[2]);
    mgr.close(no[3]);
    mgr.close(no[4]);
    mgr.close(no[5]);
    OKAY(cout);
  }catch(ErrorObj e){
    FAILED(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 7.1

  if (details) cout << "- Dateien 'test.dat' bis 'test3.dat' oeffnen: " << endl;
  try{
    mgr.open("test.dat", no[0]);
    mgr.open("test1.dat", no[1]);
    mgr.open("test2.dat", no[2]);
    mgr.open("test3.dat", no[3]);
    OKAY(cout);
  }catch(ErrorObj e){
    FAILED(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 7.2

  if (details) cout << "- Block 3 aus der Datei 'test.dat' lesen: " << endl;
  strcpy(r_block.getBlockPtr(), "");
  try { mgr.read(no[0], r_block); }
  catch(ErrorObj e){ FAILED(cout); }
  if (details) cout << "  Blockinhalt: \""
	                << r_block.getBlockPtr()
					<< "\""
					<< endl;
  if (strcmp(r_block.getBlockPtr(), "--- Block 3 ---")!=0) FAILED(cout);
  else OKAY(cout);
  if (details) cout << "-> " << mgr << endl;

  // Test 7.3

  if (details) cout << "- Block 25 aus der Datei 'test1.dat' lesen: " << endl;
  strcpy(r_block2.getBlockPtr(), "");
  try { mgr.read(no[1], r_block2); }
  catch(ErrorObj e){ FAILED(cout); }
  if (details) cout << "  Blockinhalt: \""
	                << r_block2.getBlockPtr()
					<< "\""
					<< endl;
  if (strcmp(r_block2.getBlockPtr(),
	  "------------------------- Test -------------------------")!=0)
	  FAILED(cout);
  else OKAY(cout);
  if (details) cout << "-> " << mgr << endl;

  // Test 7.4

  if (details) cout << "- Block 3 in der Datei 'test.dat' überschreiben: " << endl;
  strcpy(block3.getBlockPtr(), "+++ Block 3 +++");
  try{
    mgr.write(no[0], block3);
    OKAY(cout);
  }catch(ErrorObj e){
    FAILED(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 7.5

  if (details) cout << "- Block 3 aus der Datei 'test.dat' lesen: " << endl;
  strcpy(r_block.getBlockPtr(), "");
  try { mgr.read(no[0], r_block); }
  catch(ErrorObj e){ FAILED(cout); }
  if (details) cout << "  Blockinhalt: \""
	                << r_block.getBlockPtr()
					<< "\""
					<< endl;
  if (strcmp(r_block.getBlockPtr(), "+++ Block 3 +++")!=0) FAILED(cout);
  else OKAY(cout);
  if (details) cout << "-> " << mgr << endl;

  // Test 7.6

  if (details) cout << "- Dateien 'test8.dat' und 'test9.dat' anlegen: " << endl;
  try{
    mgr.create("test8.dat", no[4]);
    mgr.create("test9.dat", no[5]);
    OKAY(cout);
  }catch(ErrorObj e){
    FAILED(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 7.6

  if (details) cout << "- Block 1 in der Datei 'test8.dat' schreiben: " << endl;
  strcpy(block.getBlockPtr(), "---- TEXT ----");
  try{
    mgr.write(no[4], block);
    OKAY(cout);
  }catch(ErrorObj e){
    FAILED(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 7.7

  if (details) cout << "- Block 1 in der Datei 'test9.dat' schreiben: " << endl;
  strcpy(block.getBlockPtr(), "++++ TEXT ++++");
  try{
    mgr.write(no[5], block);
    OKAY(cout);
  }catch(ErrorObj e){
    FAILED(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 7.8

  if (details) cout << "- Block 1 aus der Datei 'test8.dat' lesen: " << endl;
  try { mgr.read(no[4], r_block3); }
  catch(ErrorObj e){ FAILED(cout); }
  if (details) cout << "  Blockinhalt: \""
	                << r_block3.getBlockPtr()
					<< "\""
					<< endl;
  if (strcmp(r_block3.getBlockPtr(), "---- TEXT ----")!=0) FAILED(cout);
  else OKAY(cout);
  if (details) cout << "-> " << mgr << endl;

  // Test 7.9

  if (details) cout << "- Block 1 aus der Datei 'test9.dat' lesen: " << endl;
  strcpy(r_block3.getBlockPtr(), "");
  try { mgr.read(no[5], r_block3); }
  catch(ErrorObj e){ FAILED(cout); }
  if (details) cout << "  Blockinhalt: \""
	                << r_block3.getBlockPtr()
					<< "\""
					<< endl;
  if (strcmp(r_block3.getBlockPtr(), "++++ TEXT ++++")!=0) FAILED(cout);
  else OKAY(cout);
  if (details) cout << "-> " << mgr << endl;

  // Test 8.1

  if (details)cout << "- ERROR: Datei 'test8.dat'loeschen: " << endl;
  try{
    mgr.drop("test8.dat");
    FAILED(cout);
  }catch(ErrorObj e){
    OKAY(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 8.2

  if (details)cout << "- Dateien 'test.dat' bis 'test8.dat' schliessen: " << endl;
  try{
    mgr.close(no[0]);
    mgr.close(no[1]);
    mgr.close(no[2]);
    mgr.close(no[3]);
    mgr.close(no[4]);
    mgr.close(no[6]);
    mgr.close(no[7]);
    OKAY(cout);
  }catch(ErrorObj e){
    FAILED(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 9.1

  if (details) cout << "- Dateien 'test1.dat' bis 'test8.dat' loeschen: " << endl;
  try{
    mgr.drop("test1.dat");
    mgr.drop("test2.dat");
    mgr.drop("test3.dat");
    mgr.drop("test4.dat");
    mgr.drop("test5.dat");
    mgr.drop("test6.dat");
    mgr.drop("test7.dat");
    mgr.drop("test8.dat");
    OKAY(cout);
  }catch(ErrorObj e){
    FAILED(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 9.2

  if (details) cout << "- ERROR: Datei 'test.dat' loeschen: " << endl;
  try{
    mgr.drop("test.dat");
    FAILED(cout);
  }catch(ErrorObj e){
    OKAY(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 9.3

  if (details) cout << "- ERROR: Datei 'test9.dat' loeschen: " << endl;
  try{
    mgr.drop("test9.dat");
    FAILED(cout);
  }catch(ErrorObj e){
    OKAY(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 9.3

  if (details)cout << "- Datei 'test9.dat' und 'test.dat' schliessen: " << endl;
  try{
    mgr.close(no[5]);
    mgr.close(no[0]);
    OKAY(cout);
  }catch(ErrorObj e){
    FAILED(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 9.4

  if (details) cout << "- Datei 'test9.dat' und 'test.dat' loeschen: " << endl;
  try{
    mgr.drop("test9.dat");
    mgr.drop("test.dat");
    OKAY(cout);
  }catch(ErrorObj e){
    cout << e<<endl;
    FAILED(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 9.5

  if (details) cout << "- ERROR: Datei 'test9.dat' nochmals loeschen: " << endl;
  try{
    mgr.drop("test9.dat");
    FAILED(cout);
  }catch(ErrorObj e){
    OKAY(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  // Test 9.6

  if (details) cout << "- ERROR: nicht existierende Datei 'test100.dat' loeschen: " << endl;
  try{
    mgr.drop("test100.dat");
    FAILED(cout);
  }catch(ErrorObj e){
    OKAY(cout);
  }
  if (details) cout << "-> " << mgr << endl;

  return 0;
};
