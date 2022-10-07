import { NestedTreeControl } from '@angular/cdk/tree';
import { Component, OnInit } from '@angular/core';
import { MatTreeNestedDataSource } from '@angular/material/tree';

interface CourseNode {
  name: string;
  children?: CourseNode[];
}

const TREE_DATA: CourseNode[] = [
  {
    name: ' 1.みんなの趣味の園芸',
    children: [
      {
        name: ' ①形態',
        children: [
          { name: '一年草' },
          { name: '2年草' },
          { name: '多年草' },
          { name: '低木' },
          { name: '高木' },
          { name: 'つる植物' },
        ],
      },
      {
        name: ' ②園芸分類',
        children: [
          { name: '果樹' },
          { name: '球根' },
          { name: 'コニファー' },
          { name: 'シダ' },
          { name: '水星植物' },
          { name: '熱帯植物' },
          { name: '野菜' },
          { name: '草花' },
          { name: '観葉植物' },
          { name: 'グラス' },
          { name: '山野草' },
          { name: '食中植物' },
          { name: '多肉植物' },
          { name: 'ハーブ' },
          { name: 'ラン' },
          { name: '庭木・花木' }
        ],
      },
      {
        name: ' ③特性・用途',
        children: [
          { name: '常緑性' },
          { name: 'つる性' },
          { name: '香りがある' },
          { name: '耐寒性が強い' },
          { name: '日陰でも育つ' },
          { name: '初心でも育てやすい' },
          { name: 'グラウンドカバーにできる' },
          { name: '落葉性' },
          { name: '開花期が長い' },
          { name: 'カラーリーフ' },
          { name: '生け垣向き' },
          { name: '盆栽向き' }
        ],
      },
      {
        name: ' ④花の色',
        children: [
          { name: '白' },
          { name: '赤' },
          { name: '香りがある' },
          { name: '耐寒性が強い' },
          { name: '日陰でも育つ' },
          { name: '初心でも育てやすい' },
          { name: 'グラウンドカバーにできる' },
          { name: '落葉性' },
          { name: '開花期が長い' },
          { name: 'カラーリーフ' },
          { name: '生け垣向き' },
          { name: '盆栽向き' }
        ],
      },
      {
        name: ' ⑤開花期',
        children: [
          { name: '1月' },
          { name: '2月' },
          { name: '3月' },
          { name: '4月' },
          { name: '5月' },
          { name: '6月' },
          { name: '7月' },
          { name: '8月' },
          { name: '9月' },
          { name: '10月' },
          { name: '11月' },
          { name: '12月' }
        ],
      },
    ],
  },
];

@Component({
  selector: 'app-content',
  templateUrl: './content.component.html',
  styleUrls: ['./content.component.scss']
})
export class ContentComponent implements OnInit {

  nestedDataSource = new MatTreeNestedDataSource<CourseNode>();

  nestedTreeControl = new NestedTreeControl<CourseNode>(node => node.children);

  ngOnInit(): void {

    this.nestedDataSource.data = TREE_DATA;

  }

  hasNestedChild(index: number, node: CourseNode) {
    return !!node.children && node.children.length > 0;
  }

}
