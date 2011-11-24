function sliceFileType(_fileName) {
	var _result = "";
	var _add = false;
	for(var _i = _fileName.length - 1; _i >= 0; _i--) {
		if(_add)
			_result = _fileName[_i] + _result;
		if(_fileName[_i] == '.') {
			_add = true;
		}
	}
	return _result;
}

//라이브러리에서 폴더를 제외한 이름을 리턴
function sliceLibraryPath(_filePath)
{
	var _pathStr = "";
	var _searchSlice;
	for(var _i = _filePath.length - 1; _i >= 0; _i--)
	{
		if(_filePath[_i] == '/')
		{
			_searchSlice = _i;
			break;
		}
	}
	for(var _i = _searchSlice + 1; _i < _filePath.length; _i++)
	{
		_pathStr += _filePath[_i];
	}
	return _pathStr;
}

function isCenter(_itemName)
{
	var _isItem = true;
	var _centerName = "center/";
	for(var _i = 0; _i < _centerName.length; _i++)
	{
		if(_itemName[_i] != _centerName[_i])
		{
			_isItem = false;
			break;
		}
	}
	return _isItem;
}

function isImage(_itemName)
{
	var _isItem = true;
	var _imageName = "image/";
	for(var _i = 0; _i < _imageName.length; _i++)
	{
		if(_itemName[_i] != _imageName[_i])
		{
			_isItem = false;
			break;
		}
	}
	return _isItem;
}

var doc = fl.getDocumentDOM();
 

if(doc.library.itemExists("image") == false)
	doc.library.newFolder("image");
	
if(doc.library.itemExists("center") == false)
	doc.library.newFolder("center");

if(doc.library.itemExists("_dynamic") == false)
	doc.library.newFolder("_dynamic");


var folderContents = FLfile.listFolder(sliceFileType(doc.pathURI) + "_slice");

var updateName = new Array();
var updateNameCount = 0;

for(var i = 0; i < folderContents.length; i++) {
	var sliceName = sliceFileType(folderContents[i]);
	var imageName = "image/" + sliceName;
	var centerName = "center/" + sliceName;
	
	var olderX = 0;
	var olderY = 0;
	if(doc.library.itemExists(centerName)) {
		doc.library.editItem(centerName);
		olderX = doc.getTimeline().layers[0].frames[0].elements[0].x;
		olderY = doc.getTimeline().layers[0].frames[0].elements[0].y;
		doc.selectAll();
		if(doc.selection.length)
			doc.deleteSelection();
		doc.library.deleteItem(imageName);
	}
		
	doc.editScene(0);
	if(".DS_Store" == folderContents[i])
		continue;
	doc.importFile(sliceFileType(doc.pathURI) + "_slice/" + folderContents[i]);
	doc.selectAll();
	if(doc.selection.length)
		doc.deleteSelection();
	doc.library.selectItem(folderContents[i]);
	doc.library.renameItem(sliceName);
	doc.library.moveToFolder("image", sliceName, true);
	
	var bitmapIndex = doc.library.findItemIndex(imageName);
	doc.library.items[bitmapIndex].allowSmoothing = true;
	doc.library.items[bitmapIndex].compressionType = "lossless";
	
	if(!doc.library.itemExists(centerName))
		doc.library.addNewItem("movie clip", centerName);
	
	doc.library.editItem(centerName);
	doc.library.addItemToDocument({x:0, y:0}, imageName);
	doc.getTimeline().layers[0].frames[0].elements[0].x = olderX;
	doc.getTimeline().layers[0].frames[0].elements[0].y = olderY;
	
	
	updateName[updateNameCount] = sliceName;
	updateNameCount++;
}


for(var j = 0; j < doc.library.items.length; j++) {
	var isExistUpdated = false;
	var isCenterItem = isCenter(doc.library.items[j].name);
	if(isCenterItem) {
		for(var i = 0; i < updateNameCount; i++) {
			if(sliceLibraryPath(doc.library.items[j].name) == updateName[i]) {
				isExistUpdated = true;
			}
		}
		if(!isExistUpdated) {
			doc.library.deleteItem(doc.library.items[j].name);
		}
	}
}

alert("완료.");