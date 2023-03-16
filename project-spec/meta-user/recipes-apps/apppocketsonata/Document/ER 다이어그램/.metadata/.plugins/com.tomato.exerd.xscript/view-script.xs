
var file = promptSaveFile("저장할 파일명을 입력하세요", "csv");
if(!file){
	exit();
}

var os = file.getOutputStream();
var counter = 0;
os.printf("\"No\",\"테이블명\",\"테이블ID\",\"컬럼명\",\"컬럼ID\",\"데이터타입\"\n");
select(function(it){
	return it.get("type") == "column";
}).each(function(it){
	counter++;
	
	var tableName = it.get("table").get("logical-name");
	var tableId = it.get("table").get("physical-name");
	var columnName = it.get("logical-name");
	var columnId = it.get("physical-name");
	var dataType = it.get("data-type");
	
	os.printf("%d,\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n", counter, tableName, tableId, columnName, columnId, dataType);
});

os.close();

file.openInEditor();