﻿#target photoshop//디버그 모드var VBIsDebugMode = true;//로그 파일var fileOut;//디버그 모드시 로그파일 생성if(VBIsDebugMode) {    fileOut = new File("/VBEngine/tmp/VBMakeTexture_jsx.log");    fileOut.remove();    fileOut.lineFeed = "Macintosh";    fileOut.open("w", "TEXT", "????");}//디버그 모드시 로그파일에 출력function VBDebugLog(str) {    if(VBIsDebugMode) {        fileOut.write(str + "\n");    }}//인자로 넘긴 수가 2의 승수인지 체크function VBIsPowerNum(_num) {    var powerNum = 2;    while(powerNum < _num)        powerNum = powerNum * 2;    return powerNum == _num;}//인자로 넘긴 SubPathItems를 Bounds로 만들어주는 Class//_path_points : 만들어질 vertex PathPoints//_path_points_unit_type : _path_points UnitValue type ("px", "in", "%", "ft" ...)//_bounds_unit_type : 나중에 가져올 Bounds의 UnitValue type ("px", "in", "%", "ft" ...)VBSubPathItemBoundingBox = function(_path_points, _path_points_unit_type, _bounds_unit_type) {    this.bounds = new Array();    this.path_points = _path_points;    this.path_points_unit_type = _path_points_unit_type;    this.bounds_unit_type = _bounds_unit_type;        //SubPathItems의 left구하기    this.getSubPathItemsLeft = function() {        var min = this.path_points[0].anchor[0];        for(var i = 1; i < this.path_points.length; i++) {            if(min > this.path_points[i].anchor[0])                min = this.path_points[i].anchor[0];        }        return min;    }        //SubPathItems의 top구하기    this.getSubPathItemsTop = function() {        var min = this.path_points[0].anchor[1];        for(var i = 1; i < this.path_points.length; i++) {            if(min > this.path_points[i].anchor[1])                min = this.path_points[i].anchor[1];        }        return min;    }        //SubPathItems의 right구하기    this.getSubPathItemsRight = function() {        var max = this.path_points[0].anchor[0];        for(var i = 1; i < this.path_points.length; i++) {            if(max < this.path_points[i].anchor[0])                max = this.path_points[i].anchor[0];        }        return max;    }        //SubPathItems의 bottom구하기    this.getSubPathItemsBottom = function() {        var max = this.path_points[0].anchor[1];        for(var i = 1; i < this.path_points.length; i++) {            if(max < this.path_points[i].anchor[1])                max = this.path_points[i].anchor[1];        }        return max;    }        //SubPathItems의 Bounds구하기    this.getBounds = function() {        //SubPathItems의 수치로 시작        this.bounds[0] = UnitValue(0, this.path_points_unit_type);        this.bounds[1] = UnitValue(0, this.path_points_unit_type);        this.bounds[2] = UnitValue(0, this.path_points_unit_type);        this.bounds[3] = UnitValue(0, this.path_points_unit_type);                this.bounds[0].value = this.getSubPathItemsLeft();        this.bounds[1].value = this.getSubPathItemsTop();        this.bounds[2].value = this.getSubPathItemsRight();        this.bounds[3].value = this.getSubPathItemsBottom();                //출력할 Bounds의 수치로 컨버팅        this.bounds[0].convert(this.bounds_unit_type);        this.bounds[1].convert(this.bounds_unit_type);        this.bounds[2].convert(this.bounds_unit_type);        this.bounds[3].convert(this.bounds_unit_type);                return this.bounds;    }        return this;}//Layers오브젝트중에 해당인덱스만 눈을켜주고 모두 끄기//_layers : Layers//_index : 눈을 켜줄 Layers의 인덱스function VBShowNowLayerAndHideOtherLayer(_layers, _index) {    for(var i = 0; i < _layers.length; i++) {        if(i == _index)            _layers[i].visible = true;        else            _layers[i].visible = false;    }}//해당String에 해당하는 경로가 있다면 모두 삭제하고 디렉토리 생성//_folder_path : 재생성할 경로function VBRemoveAndCreateFolder(_folder_path) {    var folder = new Folder(_folder_path);    if(folder.created) {        var fileList = folder.getFiles();        for(var i = 0; i < fileList.length; i++) {            if(fileList[i] instanceof File)                fileList[i].remove();        }    } else {        folder.create();    }}//Layers오브젝트중에 해당인덱스의 이름과 동일한 것이 있는지 검사하고 있다면 true리턴//_layers : Layers//_index : 검사할 Layers의 인덱스function VBLayerNameIsOverlab(_layers, _index) {    for(var i = 0; i < _layers.length; i++) {        if(i == _index)            continue;        if(_layers[i].name == _layers[_index].name)            return true;    }    return false;}//PathItems오브젝트중에 Layer의 이름과 동일한 PathItem이 있는지 검사하고 있다면 true리턴//_path_items : PathItems//_layer : 검사할 Layerfunction VBLayerIsHavePathItem(_layer, _path_items) {    for(var i = 0; i < _path_items.length; i++) {        if(_path_items[i].kind == PathKind.NORMALPATH) {            if(_path_items[i].name == _layer.name)                return true;        }    }    return false;}//Layers오브젝트중에 PathItem의 이름과 동일한 Layer가 있는지 검사하고 있다면 true리턴//_layers : Layers//_path_item : 검사할 PathItemfunction VBPathItemIsHaveLayer(_path_item, _layers) {    for(var i = 0; i < _layers.length; i++) {        if(_layers[i].name == _path_item.name)            return true;    }    return false;}//레이어의 바운드가 도큐먼트의 바운드를 넘는지 체크function VBIsAvailableBounds(_document, _bounds) {    if(_bounds[0].value < 0)        return false;    if(_bounds[1].value < 0)        return false;    if(_bounds[2].value > _document.width.value)        return false;    if(_bounds[3].value > _document.height.value)        return false;    return true;}//도큐먼트를 텍스쳐로 사용할수 있는지의 여부를 리턴function VBIsAvailableMakeTexture(_document) {    try {        _document.path;    } catch(error) {        alert(_document.name + "문서는 문서가 저장되어있지 않아서 VBMakeTexture를 실행할수 없습니다.");        return false;    }        if(VBIsPowerNum(_document.width.value) == false) {        alert(_document.name + "문서는 문서의 넓이가 2의승수가 아니어서 VBMakeTexture를 실행할수 없습니다.");        return false;    }    if(VBIsPowerNum(_document.height.value) == false) {        alert(_document.name + "문서는 문서의 높이가 2의승수가 아니어서 VBMakeTexture를 실행할수 없습니다.");        return false;    }        for(var i = 0; i < _document.layers.length; i++) {        if(VBLayerNameIsOverlab(_document.layers, i)) {            alert(_document.name + "문서는 문서에서 이름이 중복되는 \""+ _document.layers[i].name +"\"레이어를 발견했기때문에 VBMakeTexture를 실행할수 없습니다.");            return false;        }                if(VBLayerIsHavePathItem(_document.layers[i], _document.pathItems)) {            var sub_path_items = _document.pathItems.getByName(_document.layers[i].name).subPathItems;            if(sub_path_items.length > 1) {                alert(_document.name + "문서는 \"" + _document.layers[i].name + "\"패스가 1개이상의 패스아이템을 가지고 있기 때문에 VBMakeTexture를 실행할수 없습니다.");                return false;            }            var path_points = sub_path_items[0].pathPoints;            var pathBB = new VBSubPathItemBoundingBox(path_points, "pt", "pt");            var bounds = pathBB.getBounds();            if(VBIsAvailableBounds(_document, bounds) == false) {                alert(_document.name + "문서는 \"" + _document.layers[i].name + "\"레이어의 Path가 문서의 사이즈를 넘어가기 때문에 VBMakeTexture를 실행할수 없습니다.");                return false;            }                    } else {            var bounds = _document.layers[i].bounds;                        bounds[0].convert("pt");            bounds[1].convert("pt");            bounds[2].convert("pt");            bounds[3].convert("pt");                        bounds[0].value = bounds[0].value - 1;            bounds[1].value = bounds[1].value - 1;            bounds[2].value = bounds[2].value + 1;            bounds[3].value = bounds[3].value + 1;            if(VBIsAvailableBounds(_document, bounds) == false) {                alert(_document.name + "문서는 \"" + _document.layers[i].name + "\"레이어의 바운딩(Path를 지정하지 않았을경우 1px여백이 있는 사각형 바운딩으로 지정됨)이 문서의 사이즈를 넘어가기 때문에 VBMakeTexture를 실행할수 없습니다.");                return false;            }        }    }        return true;}//레이어 별로 잘라서 이미지를 저장하고 플러그인을 이용하여 바운드 정보를 저장function VBCropLayerAndExportUV(_document, _layer_index, _slice_folder_path, _extension) {    var bounds;    var layer = _document.layers[_layer_index]    _extension.WriteUVName(layer.name);        if(VBLayerIsHavePathItem(layer, _document.pathItems)) {        var path_points = _document.pathItems.getByName(layer.name).subPathItems[0].pathPoints;        _extension.WriteUVInt(path_points.length);                for(var i = 0; i < path_points.length; i++) {            _extension.WriteUVFloat(path_points[i].anchor[0] / _document.width.value);            _extension.WriteUVFloat(path_points[i].anchor[1] / _document.height.value);        }                var pathBB = new VBSubPathItemBoundingBox(path_points, "pt", "pt");        bounds = pathBB.getBounds();    } else {        bounds = layer.bounds;                bounds[0].convert("pt");        bounds[1].convert("pt");        bounds[2].convert("pt");        bounds[3].convert("pt");                bounds[0].value = bounds[0].value - 1;        bounds[1].value = bounds[1].value - 1;        bounds[2].value = bounds[2].value + 1;        bounds[3].value = bounds[3].value + 1;                _extension.WriteUVInt(4);                _extension.WriteUVFloat(bounds[0].value / _document.width.value);        _extension.WriteUVFloat(bounds[1].value / _document.height.value);                _extension.WriteUVFloat(bounds[2].value / _document.width.value);        _extension.WriteUVFloat(bounds[1].value / _document.height.value);                _extension.WriteUVFloat(bounds[2].value / _document.width.value);        _extension.WriteUVFloat(bounds[3].value / _document.height.value);                _extension.WriteUVFloat(bounds[0].value / _document.width.value);        _extension.WriteUVFloat(bounds[3].value / _document.height.value);     }        VBShowNowLayerAndHideOtherLayer(_document.layers, _layer_index);    _document.crop(bounds);    _document.saveAs(new File(_slice_folder_path + "/" + layer.name + ".png"), new PNGSaveOptions, true);}//열려져 있는 모든 도큐먼트에 대해 Make Texture 스크립트 실행function main() {    //엔진의 리소스 크기의 단위는 픽셀사이즈임    if(app.preferences.rulerUnits != Units.PIXELS) {        alert("VBEngine의 Ruler Units은 Pixels이어야만 합니다. 그래서 바꾸겠습니다.");        app.preferences.rulerUnits = Units.PIXELS;    }    VBDebugLog("룰러 설정");        //열려있는 모든 도큐먼트에대해 MakeTexture실행    for(var i = 0; i < app.documents.length; i++) {        var document = app.documents[i];        //활성화        app.activeDocument = document;                VBDebugLog(i + "번째문서 Active후 available 체크");                //텍스쳐 생성이 가능한지 판단        if(VBIsAvailableMakeTexture(document)) {            if(document.saved == false)                document.save();                        Folder.current = File(document.fullName).parent;                        //PNG 저장            var fileName = document.fullName.fsName.replace(/^[\u0000-\ud7a3]+\/+|\.[^\.]*$/g, "");             document.saveAs(new File(Folder.current + "/" + fileName + ".png"), new PNGSaveOptions, true);             VBDebugLog("png 저장");                        //UV 저장            var uvPath = Folder.current.fsName + "/" + fileName + ".uv";              VBDebugLog("uv 저장");                        //플러그인 로드             var extension = new ExternalObject("lib:VBPhotoshopPlugIn.framework");             extension.OpenUVFile(uvPath);            VBDebugLog("plug in 호출");                        //도큐먼트 사이즈 저장            extension.WriteUVInt(document.width.value);            extension.WriteUVInt(document.height.value);                        //slice폴더 생성            Folder.current = File(document.fullName).parent;            var slice_folder_path = Folder.current.fsName + "/" + fileName + "_slice";            VBRemoveAndCreateFolder(slice_folder_path);                        //레이어 별로 slice및 bound UV정보 저장            for(var j = 0; j < document.layers.length; j++) {                VBDebugLog(j + "번째 레이어 slice 저장 + bound 저장");                document.suspendHistory("mark", "VBCropLayerAndExportUV(document,j,slice_folder_path,extension)");                executeAction(charIDToTypeID("undo"), undefined, DialogModes.NO);            }                        //uv파일 닫기            extension.CloseUVFile();            VBDebugLog("UV파일 닫기");                        //VBEngine/tmp/photoshopPSDName 에 PSD파일명 경로와 확장자 제거하고 저장            extension.GetFileName(app.documents[0].fullName.fsName.replace(/\.[^\.]*$/g, ""));            VBDebugLog("VBEngine/tmp/photoshopPSDName에 파일네임 저장");                        //플래쉬 실행후 VBImportObj실행            var appleScript = "tell application \"Finder\"\nset aList to folders in folder \"Applications\" of startup disk\nrepeat with the_item in aList\nif \"Flash CS\" is in the_item\'s name then\nset the_application to the_item\'s name\nexit repeat\nend if\nend repeat\nend tell\ntell application \"System Events\" to if not UI elements enabled then\nset UI elements enabled to true\nif not UI elements enabled then error number -128 \nend if \nrepeat 2 times\ntell application the_application to activate\nend repeat\ntell application \"System Events\"\ntell process the_application\ntell menu bar 1\ntell menu bar item \"Commands\"\ntell menu \"Commands\"\nclick menu item \"VBImportObj\"\nend tell\nend tell\nend tell\nend tell\nend tell";            extension.OpenFlashAndSync(appleScript);            VBDebugLog("apple script실행");                        //플러그인 언로드            extension.unload();            VBDebugLog("플러그 인 언로드");        }    }    return true;}VBDebugLog(main() ? "완료" : "문제 있음");//로그 파일 닫기if(VBIsDebugMode) {    fileOut.close();}