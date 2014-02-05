Features :
1. He thong ho tro cac type file anh sau : jpg, jpeg, png, bmp, tiff, ico, ppm
2. Load mot database anh theo 2 tinh huong :
    - Co so du lieu anh moi : load tat ca anh trong thu muc
    - Co so du lieu anh da duoc xu ly : load anh tu file database.meta,
                                        load features.meta neu co
                                        load metadata cua cac image
                                        load map.meta
3. Save database :
    - luu file database.meta
    - luu file features.meta
    - luu file metadata cua cac image
4. Features extract : Color Histogram, Hu Moments, Matrix Cooccurrences (Ho tro plugin)
5. Browser co ban : zoom, chuot, phim mui ten
6. View duoi dang luoi SOM co ho tro fullscreen, animation
7. View thong tin cua database cung nhu cua tung file anh (View Metadata) ho tro xem nhieu images
8. Xem anh nguyen goc (View Image) ho tro xem nhieu images
9. Import them anh vao CSDL
10. Su dung thuat toan SOM dinh vi tri cho cac image duoi dang luoi
11. Su dung thuat toan rearrangement de khac phuc diem yeu cua thuat toan SOM (mot case co nhieu image)
12. Cac extractor duoc viet theo dang da hinh, de dang cho viec them extractor moi,
    cung nhu sau nay ho tro cho tinh nang Plugins
13. He thong ho tro plugins cho cac extractor, co giao dien cho phep them va xoa Plugin
14. Capture the screen
15. Ho tro save va load weights

Co van de :
Nang cap truong hop khoang cach aqe cho classify
Sua loi voi OpenGL
may cai loi fix application

29/09/2011 :
1. Test save features of images va save database
2. Test import
3. Test load map
4. Test search
5. Sua loi load du lieu len nhung khong cap nhat mau tren GLSOMScene de ve
6. Test classification
7. Hoan thanh Information
8. Hoan thanh delete Image

28/09/2011 :
1. Sua loi khong cap nhat plugin moi cho MapSOM
2. Hoan thanh loadHeader va loadCodes trong tinh nang load map
3. Hoan thanh tinh nang load map
4. Hoan thanh load weight
5. Da xu ly truong hop trung ten trong qua trinh import
6. Code xong import (da test)
7. Code xong search (da test)
8. Code xong classify (da test)

27/09/2011 :
1. Hoan thanh chuc nang Init tren Form Indexing
2. Hoan thanh chuc nang Save Weight tren Form Indexing
3. Hoan thanh chuc nang Ordering, Convergence, Visual, Rearrangmenet tren Form Indexing
4. Hoan thanh chuc nang Save map as
5. Lam load map.meta (da test)

26/09/2011 :
1. Hoan thanh save map.meta
2. Them phan kiem tra xem mot descriptor duoc chon de indexing co plugin ho tro trong he thong khong
3. Sua lai GridSOM, MapSOM, GLSOMScene de ho tro cho xdim va ydim
4. Sua lai Form Indexing
5. Hoan thanh tinh nang xem Codes (da test)

25/09/2011 :
1. Ho tro plugins cho he thong
2. Code xong 4 plugins extractor (da test)
3. Them ham about cho cac plugins
4. Hoan thanh chuc nang Capture the screen
5. Sua loi voi su kien keyPressEvent
6. Khac phuc mot phan loi o tinh nang Fullscreen
7. Hoan thanh Form Plugin Dialog

24/09/2011 :
1. Xong Polymorphism cho cac Extractor
2. Sua xong he thong de thich hop voi Polymorphism cua Extractor
3. Code chuc nang Capture the screen

23/09/2011 :
1. Da ve them mot con so the hien so luong images tai mot cell
2. Ho tro cho viec ve nen
3. Polymorphism cho cac Extractor (chua hoan thanh)

21/09/2011 :
1. Sua lai cach tinh toan cua MatrixCooccurrence2
2. Hoan thanh phan chon features trong form Indexing
3. Hoan thanh form Indexing
4. Sua cac tinh nang tron View
5. Hoan thanh tinh nang MDI

20/09/2011 :
1. Da test voi MatrixCooccurrenceExtractor
2. Da test xong Rearrangement

19/09/2011 :
1. Sua cach hoat dong cua cac form
2. Sua form View Image va View Metadata cho phep xem noi dung mot loat anh
3. Da test MatrixCooccurrence2Extractor
4. Da kiem tra ho tro nhieu GLSOMScene tren CenterWidget nhung phai xu ly rat phuc tap nen THOI
5. Da test init
6. Da test training nhung chua test voi MatrixCooccurrence1
7. Da test visual
8. Ho tro bat qua lai giua Normal va SOM

18/09/2011 :
1. Hoan thanh code cua visual (chua test)
2. Hoan thanh code cua training (chua test)
3. Da ho tro MatrixCooccurrence2Extractor (chua test)
4. Hoan thanh code cua rearrangement (chua test)

16/09/2011 :
1. Hoan thanh code init cua SOM (chua test)

11/09/2011 :
1. Hoan tat 3 ham extract feature voi thong bao tien trinh extract
2. Hoan thanh viec them danh sach feature vao Form Feature Extract
3. Save feature
4. Sua form View Metadata
5. Hoan thanh Form Information
6. Hoan thanh Form View Image
7. Sua lai khong xoa dialog
8. Xu ly de cac Form View Image va Form View Metadata mo len dung vi tri cu

10/09/2011 :
1. Tach tinh nang load thanh loadFromMetadata va loadImages
2. Tach tinh nang save thanh saveMetaOfDatabase
3. Sua xong giao dien Form Feature Extract
4. Them phan kiem tra loi tron Form Feature Extract
5. Hoan thanh thong bao tien trinh Feature Extract

09/09/2011 :
1. Lam menu View
2. Kiem tra he thong co ho tro OpenGL hay khong
3. Thiet lap sizeHint cho cua so
4. Fix loi delete du lieu
5. Tinh nang ve lai csdl anh ve tinh trang ban dau
6. Hoan thanh tinh nang Animation
7. Da kiem tra cac extractor
8. Lam menu popup va form cho phep xem feature

08/09/2011 :
1. Tao doi tuong co ban GridSOM de luu luoi SOM
2. Sua lai giao dien giua glSOMScene tu BaseImage thanh GridSOM

03/09/2011 :
1. Kiem tra lai load du lieu (xem xet co can dung thread hay khong) -> quyet dinh khong can dung
